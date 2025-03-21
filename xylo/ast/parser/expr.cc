#include "../parser.h"

using namespace xylo;

XYLO_API std::optional<SyntaxError> Parser::parseExpr(int precedence, peff::RcObjectPtr<ExprNode> &exprOut) {
	Token *prefixToken;

	std::optional<SyntaxError> syntaxError;
	peff::RcObjectPtr<ExprNode> lhs, rhs;

	if ((syntaxError = expectToken((prefixToken = peekToken()))))
		goto genBadExpr;

	switch (prefixToken->tokenId) {
		case TokenId::ThisKeyword:
		case TokenId::ScopeOp:
		case TokenId::Id: {
			IdRefPtr idRefPtr;
			if ((syntaxError = parseIdRef(idRefPtr)))
				goto genBadExpr;
			if (!(lhs = peff::allocAndConstruct<IdRefExprNode>(resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), std::move(idRefPtr))))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::At: {
			nextToken();
			IdRefPtr idRefPtr;
			if ((syntaxError = parseIdRef(idRefPtr)))
				goto genBadExpr;
			if (!(lhs = peff::allocAndConstruct<MacroCallExprNode>(resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), std::move(idRefPtr))))
				return genOutOfMemoryError();

			Token *lParentheseToken, *rParentheseToken;
			if ((syntaxError = expectToken((lParentheseToken = nextToken()), TokenId::LParenthese)))
				goto genBadExpr;

			// TODO: Parse arguments.

			if ((syntaxError = expectToken((rParentheseToken = nextToken()), TokenId::RParenthese)))
				goto genBadExpr;
			break;
		}
		case TokenId::LParenthese: {
			nextToken();

			if ((syntaxError = parseExpr(0, lhs)))
				goto genBadExpr;

			Token *rParentheseToken;

			if ((syntaxError = expectToken((rParentheseToken = nextToken()), TokenId::RParenthese)))
				goto genBadExpr;
			break;
		}
		case TokenId::IntLiteral: {
			if (!(lhs = peff::allocAndConstruct<I32LiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(),
					  ((IntTokenExtension *)prefixToken->exData.get())->data)))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::LongLiteral: {
			if (!(lhs = peff::allocAndConstruct<I64LiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(),
					  ((LongTokenExtension *)prefixToken->exData.get())->data)))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::UIntLiteral: {
			if (!(lhs = peff::allocAndConstruct<U32LiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(),
					  ((UIntTokenExtension *)prefixToken->exData.get())->data)))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::ULongLiteral: {
			if (!(lhs = peff::allocAndConstruct<U64LiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(),
					  ((ULongTokenExtension *)prefixToken->exData.get())->data)))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::StringLiteral: {
			peff::String s(resourceAllocator.get());

			if (!peff::copyAssign(s, ((StringTokenExtension *)prefixToken->exData.get())->data))
				return genOutOfMemoryError();

			if (!(lhs = peff::allocAndConstruct<StringLiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(),
					  std::move(s))))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::F32Literal: {
			if (!(lhs = peff::allocAndConstruct<F32LiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(),
					  ((F32TokenExtension *)prefixToken->exData.get())->data)))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::F64Literal: {
			if (!(lhs = peff::allocAndConstruct<F64LiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(),
					  ((F64TokenExtension *)prefixToken->exData.get())->data)))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::TrueKeyword: {
			if (!(lhs = peff::allocAndConstruct<BoolLiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(),
					  true)))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::FalseKeyword: {
			if (!(lhs = peff::allocAndConstruct<BoolLiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(),
					  false)))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::NullptrKeyword: {
			if (!(lhs = peff::allocAndConstruct<NullptrLiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get())))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::LBracket: {
			nextToken();

			peff::RcObjectPtr<DesignatedInitializerExprNode> initializerExpr;

			if (!(initializerExpr = peff::allocAndConstruct<DesignatedInitializerExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get())))
				return genOutOfMemoryError();

			peff::RcObjectPtr<ExprNode> curExpr;

			TokenId matchingTokens[] = {
				TokenId::RBracket,
				TokenId::Semicolon
			};

			Token *currentToken;

			for (;;) {
				if ((syntaxError = expectToken((currentToken = nextToken()), TokenId::Dot))) {
					if (!syntaxErrors.pushBack(std::move(syntaxError.value())))
						return genOutOfMemoryError();
					syntaxError.reset();
					if ((syntaxError = lookaheadUntil(std::size(matchingTokens), matchingTokens)))
						goto genBadExpr;
					goto genBadExpr;
				}

				if ((syntaxError = expectToken((currentToken = nextToken()), TokenId::Id))) {
					if (!syntaxErrors.pushBack(std::move(syntaxError.value())))
						return genOutOfMemoryError();
					syntaxError.reset();
					if (!syntaxErrors.pushBack(SyntaxError(currentToken->index, SyntaxErrorKind::ExpectingId)))
						return genOutOfMemoryError();
				}

				peff::String copiedName(resourceAllocator.get());
				if (!copiedName.build(currentToken->sourceText)) {
					return genOutOfMemoryError();
				}

				if ((syntaxError = expectToken((currentToken = nextToken()), TokenId::AssignOp))) {
					if (!syntaxErrors.pushBack(std::move(syntaxError.value())))
						return genOutOfMemoryError();
					syntaxError.reset();
					if (!syntaxErrors.pushBack(SyntaxError(currentToken->index, ExpectingSingleTokenErrorExData{ TokenId::AssignOp })))
						return genOutOfMemoryError();
				}

				if ((syntaxError = parseExpr(0, curExpr))) {
					if (!syntaxErrors.pushBack(std::move(syntaxError.value())))
						return genOutOfMemoryError();
					syntaxError.reset();
					goto genBadExpr;
				}

				currentToken = peekToken();

				if (!initializerExpr->fields.pushBack({ std::move(copiedName), std::move(curExpr) })) {
					return genOutOfMemoryError();
				}

				if (currentToken->tokenId != TokenId::Comma)
					break;

				nextToken();
			}

			if ((syntaxError = expectToken(currentToken = nextToken(), TokenId::RBracket))) {
				if (!syntaxErrors.pushBack(std::move(syntaxError.value())))
					return genOutOfMemoryError();
				syntaxError.reset();
				if ((syntaxError = lookaheadUntil(std::size(matchingTokens), matchingTokens)))
					goto genBadExpr;
			}

			lhs = initializerExpr.get();

			break;
		}
		case TokenId::LBrace: {
			nextToken();

			peff::RcObjectPtr<InitializerListExprNode> initializerExpr;

			if (!(initializerExpr = peff::allocAndConstruct<InitializerListExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get())))
				return genOutOfMemoryError();

			peff::RcObjectPtr<ExprNode> curExpr;

			TokenId matchingTokens[] = {
				TokenId::RBracket,
				TokenId::Semicolon
			};

			Token *currentToken;

			for (;;) {
				if ((syntaxError = parseExpr(0, curExpr))) {
					if (!syntaxErrors.pushBack(std::move(syntaxError.value())))
						return genOutOfMemoryError();
					syntaxError.reset();
					goto genBadExpr;
				}

				currentToken = peekToken();

				if (!initializerExpr->elements.pushBack(std::move(curExpr))) {
					return genOutOfMemoryError();
				}

				if (prefixToken->tokenId != TokenId::Comma)
					break;

				nextToken();
			}

			if ((syntaxError = expectToken(currentToken = nextToken(), TokenId::RBrace))) {
				if (!syntaxErrors.pushBack(std::move(syntaxError.value())))
					return genOutOfMemoryError();
				syntaxError.reset();
				if ((syntaxError = lookaheadUntil(std::size(matchingTokens), matchingTokens)))
					goto genBadExpr;
			}

			lhs = initializerExpr.get();

			break;
		}
		case TokenId::SubOp: {
			nextToken();

			peff::RcObjectPtr<UnaryExprNode> expr;

			if (!(expr = peff::allocAndConstruct<UnaryExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), UnaryOp::Neg, nullptr)))
				return genOutOfMemoryError();

			if ((syntaxError = parseExpr(131, expr->operand))) {
				goto genBadExpr;
			}

			lhs = expr.get();
			break;
		}
		case TokenId::NotOp: {
			nextToken();

			peff::RcObjectPtr<UnaryExprNode> expr;

			if (!(expr = peff::allocAndConstruct<UnaryExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), UnaryOp::Neg, nullptr)))
				return genOutOfMemoryError();

			if ((syntaxError = parseExpr(131, expr->operand))) {
				goto genBadExpr;
			}

			lhs = expr.get();
			break;
		}
		case TokenId::LNotOp: {
			nextToken();

			peff::RcObjectPtr<UnaryExprNode> expr;

			if (!(expr = peff::allocAndConstruct<UnaryExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), UnaryOp::Neg, nullptr)))
				return genOutOfMemoryError();

			if ((syntaxError = parseExpr(131, expr->operand))) {
				goto genBadExpr;
			}

			lhs = expr.get();
			break;
		}
		case TokenId::AndOp: {
			nextToken();

			peff::RcObjectPtr<UnaryExprNode> expr;

			if (!(expr = peff::allocAndConstruct<UnaryExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), UnaryOp::AddressOf, nullptr)))
				return genOutOfMemoryError();

			if ((syntaxError = parseExpr(131, expr->operand))) {
				goto genBadExpr;
			}

			lhs = expr.get();
			break;
		}
		case TokenId::MulOp: {
			nextToken();

			peff::RcObjectPtr<UnaryExprNode> expr;

			if (!(expr = peff::allocAndConstruct<UnaryExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), UnaryOp::Dereference, nullptr)))
				return genOutOfMemoryError();

			if ((syntaxError = parseExpr(131, expr->operand))) {
				goto genBadExpr;
			}

			lhs = expr.get();
			break;
		}
		case TokenId::SizeofKeyword: {
			nextToken();

			peff::RcObjectPtr<UnaryExprNode> expr;

			if (!(expr = peff::allocAndConstruct<UnaryExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), UnaryOp::Sizeof, nullptr)))
				return genOutOfMemoryError();

			if ((syntaxError = parseExpr(131, expr->operand))) {
				goto genBadExpr;
			}

			lhs = expr.get();
			break;
		}
		case TokenId::TypenameKeyword: {
			nextToken();

			peff::RcObjectPtr<TypeNameExprNode> expr;

			if (!(expr = peff::allocAndConstruct<TypeNameExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), UnaryOp::Sizeof, nullptr)))
				return genOutOfMemoryError();

			expr->typeNameTokenIndex = prefixToken->index;

			if ((syntaxError = parseTypeName(expr->type))) {
				goto genBadExpr;
			}

			lhs = expr.get();
			break;
		}
		default:
			nextToken();
			return SyntaxError(
				TokenRange{ prefixToken->index },
				SyntaxErrorKind::ExpectingExpr);
	}

	Token *infixToken;

	for (;;) {
		switch ((infixToken = peekToken())->tokenId) {
			case TokenId::LParenthese: {
				if (precedence > 140)
					goto end;
				nextToken();

				peff::RcObjectPtr<CallExprNode> expr;

				if (!(expr = peff::allocAndConstruct<CallExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), nullptr, peff::DynArray<peff::RcObjectPtr<ExprNode>>{ resourceAllocator.get() })))
					return genOutOfMemoryError();

				expr->target = lhs;
				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				expr->lParentheseTokenIndex = infixToken->index;

				if ((syntaxError = parseArgs(expr->args, expr->idxCommaTokens))) {
					goto genBadExpr;
				}

				Token *rParentheseToken;

				if ((syntaxError = expectToken((rParentheseToken = nextToken()), TokenId::RParenthese)))
					goto genBadExpr;

				expr->rParentheseTokenIndex = rParentheseToken->index;

				lhs = expr.get();
				break;
			}
			case TokenId::LBracket: {
				if (precedence > 140)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::Add, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(0, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				Token *rBracketToken;

				if ((syntaxError = expectToken((rBracketToken = nextToken()), TokenId::RBracket)))
					goto genBadExpr;

				lhs = expr.get();
				break;
			}
			case TokenId::Dot: {
				if (precedence > 140)
					goto end;
				nextToken();

				peff::RcObjectPtr<HeadedIdRefExprNode> expr;

				if (!(expr = peff::allocAndConstruct<HeadedIdRefExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), lhs.get(), IdRefPtr{})))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseIdRef(expr->idRefPtr)))
					goto genBadExpr;

				lhs = expr.get();
				break;
			}
			case TokenId::AsKeyword: {
				if (precedence > 130)
					goto end;
				nextToken();

				peff::RcObjectPtr<CastExprNode> expr;

				if (!(expr = peff::allocAndConstruct<CastExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), nullptr, lhs.get())))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseTypeName(expr->targetType)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->targetType->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}

			case TokenId::MulOp: {
				if (precedence > 120)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::Mul, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(121, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}
			case TokenId::DivOp: {
				if (precedence > 120)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::Div, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(121, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}
			case TokenId::ModOp: {
				if (precedence > 120)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::Mod, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(121, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}

			case TokenId::AddOp: {
				if (precedence > 110)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::Add, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(111, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}
			case TokenId::SubOp: {
				if (precedence > 110)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::Sub, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(111, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}

			case TokenId::LshOp: {
				if (precedence > 100)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::Shl, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(101, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}
			case TokenId::RshOp: {
				if (precedence > 100)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::Shr, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(101, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}

			case TokenId::GtOp: {
				if (precedence > 80)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::Gt, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(81, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}
			case TokenId::GtEqOp: {
				if (precedence > 80)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::GtEq, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(81, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}
			case TokenId::LtOp: {
				if (precedence > 80)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::Lt, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(81, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}
			case TokenId::LtEqOp: {
				if (precedence > 80)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::LtEq, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(81, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}

			case TokenId::EqOp: {
				if (precedence > 70)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::Eq, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(71, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}
			case TokenId::NeqOp: {
				if (precedence > 70)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::Neq, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(71, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}

			case TokenId::AndOp: {
				if (precedence > 60)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::And, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(61, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}

			case TokenId::XorOp: {
				if (precedence > 50)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::Xor, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(51, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}

			case TokenId::OrOp: {
				if (precedence > 40)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::Or, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(41, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}

			case TokenId::LAndOp: {
				if (precedence > 30)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::Eq, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(31, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}

			case TokenId::LOrOp: {
				if (precedence > 20)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::LOr, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(21, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}

			case TokenId::Question: {
				if (precedence > 10)
					goto end;
				nextToken();

				peff::RcObjectPtr<TernaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<TernaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), lhs.get(), nullptr, nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(10, expr->lhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->lhs->tokenRange.endIndex;

				Token *colonToken;
				if ((syntaxError = expectToken((colonToken = nextToken()), TokenId::Colon)))
					goto genBadExpr;

				expr->tokenRange.endIndex = colonToken->index;

				if ((syntaxError = parseExpr(10, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}

			case TokenId::AssignOp: {
				if (precedence > 1)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::Assign, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(0, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}
			case TokenId::AddAssignOp: {
				if (precedence > 1)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::AddAssign, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(0, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}
			case TokenId::SubAssignOp: {
				if (precedence > 1)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::SubAssign, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(0, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}
			case TokenId::MulAssignOp: {
				if (precedence > 1)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::MulAssign, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(0, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}
			case TokenId::DivAssignOp: {
				if (precedence > 1)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::DivAssign, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(0, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}
			case TokenId::AndAssignOp: {
				if (precedence > 1)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::AndAssign, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(0, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}
			case TokenId::OrAssignOp: {
				if (precedence > 1)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::OrAssign, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(0, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}
			case TokenId::XorAssignOp: {
				if (precedence > 1)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::XorAssign, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(0, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}
			case TokenId::LshAssignOp: {
				if (precedence > 1)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::ShlAssign, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(0, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}
			case TokenId::RshAssignOp: {
				if (precedence > 1)
					goto end;
				nextToken();

				peff::RcObjectPtr<BinaryExprNode> expr;

				if (!(expr = peff::allocAndConstruct<BinaryExprNode>(
						  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), BinaryOp::ShrAssign, lhs.get(), nullptr)))
					return genOutOfMemoryError();

				expr->tokenRange = lhs->tokenRange;
				expr->tokenRange.endIndex = infixToken->index;

				if ((syntaxError = parseExpr(0, expr->rhs)))
					goto genBadExpr;

				expr->tokenRange.endIndex = expr->rhs->tokenRange.endIndex;

				lhs = expr.get();
				break;
			}
		}
	}

	exprOut = lhs;

end:
	return {};

genBadExpr:
	if (!(exprOut = peff::allocAndConstruct<BadExprNode>(resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), lhs.get())))
		return genOutOfMemoryError();
	exprOut->tokenRange = { prefixToken->index, idxCurrentToken };
	exprOut->incRef();
	return syntaxError;
}
