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
		default:
			nextToken();
			return SyntaxError(
				TokenRange{ prefixToken->index },
				SyntaxErrorKind::ExpectingExpr);
	}

	return {};

genBadExpr:
	if (!(exprOut = peff::allocAndConstruct<BadExprNode>(resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get())))
		return genOutOfMemoryError();
	exprOut->tokenRange = { prefixToken->index, idxCurrentToken };
	exprOut->incRef();
	return syntaxError;
}
