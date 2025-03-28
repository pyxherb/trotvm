#include "../parser.h"

using namespace xylo;

XYLO_API std::optional<SyntaxError> Parser::parseVarDefs(peff::DynArray<VarDefEntryPtr> &varDefEntries) {
	Token *currentToken;
	std::optional<SyntaxError> syntaxError;
	peff::RcObjectPtr<TypeNameNode> type;
	peff::RcObjectPtr<ExprNode> initialValue;

	for (;;) {
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

		if ((currentToken = peekToken())->tokenId == TokenId::Colon) {
			nextToken();

			if ((syntaxError = parseTypeName(type))) {
				if (!syntaxErrors.pushBack(std::move(syntaxError.value())))
					return genOutOfMemoryError();
				syntaxError.reset();
			}
		}

		if ((currentToken = peekToken())->tokenId == TokenId::AssignOp) {
			nextToken();

			if ((syntaxError = parseExpr(0, initialValue))) {
				if (!syntaxErrors.pushBack(std::move(syntaxError.value())))
					return genOutOfMemoryError();
				syntaxError.reset();
			}
		}

		VarDefEntryPtr entry(
			peff::allocAndConstruct<VarDefEntry>(
				resourceAllocator.get(),
				ASTNODE_ALIGNMENT,
				resourceAllocator.get(),
				std::move(copiedName),
				type.get(),
				initialValue.get()));

		if (!entry) {
			return genOutOfMemoryError();
		}

		if (!varDefEntries.pushBack(std::move(entry))) {
			return genOutOfMemoryError();
		}

		if ((currentToken = peekToken())->tokenId != TokenId::Comma) {
			break;
		}

		nextToken();
	}

	return {};
}

XYLO_API std::optional<SyntaxError> Parser::parseStmt(peff::RcObjectPtr<StmtNode> &stmtOut) {
	Token *prefixToken;

	std::optional<SyntaxError> syntaxError;

	if ((syntaxError = expectToken((prefixToken = peekToken()))))
		goto genBadStmt;

	switch (prefixToken->tokenId) {
		case TokenId::IfKeyword: {
			nextToken();

			peff::RcObjectPtr<IfStmtNode> ifStmt;

			if (!(ifStmt = peff::allocAndConstruct<IfStmtNode>(resourceAllocator.get(), ASTNODE_ALIGNMENT, resourceAllocator.get(), mod, nullptr, nullptr, nullptr))) {
				return genOutOfMemoryError();
			}

			stmtOut = ifStmt.get();

			Token *lParentheseToken = peekToken();

			if ((syntaxError = expectToken(lParentheseToken, TokenId::LParenthese))) {
				goto genBadStmt;
			}

			nextToken();

			{
				const TokenId skippingTerminativeToken[] = {
					TokenId::RParenthese,
					TokenId::Semicolon,
					TokenId::RBrace
				};

				if ((syntaxError = parseExpr(0, ifStmt->cond))) {
					if ((syntaxError = lookaheadUntil(std::size(skippingTerminativeToken), skippingTerminativeToken))) {
						goto genBadStmt;
					}
					goto genBadStmt;
				}
			}

			Token *rParentheseToken = peekToken();

			if ((syntaxError = expectToken(rParentheseToken, TokenId::RParenthese))) {
				goto genBadStmt;
			}

			nextToken();

			if ((syntaxError = parseStmt(ifStmt->trueBody))) {
				goto genBadStmt;
			}

			Token *elseToken = peekToken();

			if (elseToken->tokenId == TokenId::ElseKeyword) {
				nextToken();

				if ((syntaxError = parseStmt(ifStmt->falseBody))) {
					goto genBadStmt;
				}
			}

			break;
		}
		case TokenId::ForKeyword: {
			nextToken();

			peff::RcObjectPtr<ForStmtNode> forStmt;

			if (!(forStmt = peff::allocAndConstruct<ForStmtNode>(
					  resourceAllocator.get(),
					  ASTNODE_ALIGNMENT,
					  resourceAllocator.get(),
					  mod,
					  peff::DynArray<VarDefEntryPtr>(resourceAllocator.get()),
					  nullptr,
					  nullptr,
					  nullptr))) {
				return genOutOfMemoryError();
			}

			stmtOut = forStmt.get();

			Token *lParentheseToken = peekToken();

			if ((syntaxError = expectToken(lParentheseToken, TokenId::LParenthese))) {
				goto genBadStmt;
			}

			nextToken();

			Token *varDefSeparatorToken;
			Token *condSeparatorToken;
			Token *rParentheseToken;
			{
				const TokenId skippingTerminativeToken[] = {
					TokenId::RParenthese,
					TokenId::Semicolon,
					TokenId::RBrace
				};

				if ((varDefSeparatorToken = peekToken())->tokenId != TokenId::Semicolon) {
					Token *letToken;
					if ((syntaxError = expectToken((letToken = peekToken()), TokenId::LetKeyword))) {
						goto genBadStmt;
					}
					nextToken();

					if ((syntaxError = parseVarDefs(forStmt->varDefEntries))) {
						goto genBadStmt;
					}

					if ((syntaxError = expectToken((varDefSeparatorToken = peekToken()), TokenId::Semicolon))) {
						goto genBadStmt;
					}
				} else {
					nextToken();
				}

				if ((condSeparatorToken = peekToken())->tokenId != TokenId::Semicolon) {
					if ((syntaxError = parseExpr(0, forStmt->cond))) {
						if ((syntaxError = lookaheadUntil(std::size(skippingTerminativeToken), skippingTerminativeToken))) {
							goto genBadStmt;
						}
						goto genBadStmt;
					}

					if ((syntaxError = expectToken((condSeparatorToken = peekToken()), TokenId::Semicolon))) {
						goto genBadStmt;
					}
				} else {
					nextToken();
				}

				if ((rParentheseToken = peekToken())->tokenId != TokenId::RParenthese) {
					if ((syntaxError = parseExpr(0, forStmt->step))) {
						if ((syntaxError = lookaheadUntil(std::size(skippingTerminativeToken), skippingTerminativeToken))) {
							goto genBadStmt;
						}
						goto genBadStmt;
					}

					if ((syntaxError = expectToken((rParentheseToken = peekToken()), TokenId::RParenthese))) {
						goto genBadStmt;
					}
				} else {
					nextToken();
				}
			}

			nextToken();

			if ((syntaxError = parseStmt(forStmt->body))) {
				goto genBadStmt;
			}

			break;
		}
		case TokenId::WhileKeyword: {
			nextToken();

			peff::RcObjectPtr<WhileStmtNode> whileStmt;

			if (!(whileStmt = peff::allocAndConstruct<WhileStmtNode>(
					  resourceAllocator.get(),
					  ASTNODE_ALIGNMENT,
					  resourceAllocator.get(),
					  mod,
					  nullptr,
					  nullptr))) {
				return genOutOfMemoryError();
			}

			stmtOut = whileStmt.get();

			Token *lParentheseToken = peekToken();

			if ((syntaxError = expectToken(lParentheseToken, TokenId::LParenthese))) {
				goto genBadStmt;
			}

			nextToken();

			Token *rParentheseToken;
			{
				const TokenId skippingTerminativeToken[] = {
					TokenId::RParenthese,
					TokenId::Semicolon,
					TokenId::RBrace
				};

				if ((syntaxError = parseExpr(0, whileStmt->cond))) {
					if ((syntaxError = lookaheadUntil(std::size(skippingTerminativeToken), skippingTerminativeToken))) {
						goto genBadStmt;
					}
					goto genBadStmt;
				}

				if ((syntaxError = expectToken((rParentheseToken = peekToken()), TokenId::RParenthese))) {
					goto genBadStmt;
				}

				nextToken();
			}

			if ((syntaxError = parseStmt(whileStmt->body))) {
				goto genBadStmt;
			}

			break;
		}
		case TokenId::DoKeyword: {
			nextToken();

			peff::RcObjectPtr<WhileStmtNode> whileStmt;

			if (!(whileStmt = peff::allocAndConstruct<WhileStmtNode>(
					  resourceAllocator.get(),
					  ASTNODE_ALIGNMENT,
					  resourceAllocator.get(),
					  mod,
					  nullptr,
					  nullptr))) {
				return genOutOfMemoryError();
			}

			stmtOut = whileStmt.get();

			whileStmt->isDoWhile = true;

			if ((syntaxError = parseStmt(whileStmt->body))) {
				goto genBadStmt;
			}

			Token *whileToken = peekToken();

			if ((syntaxError = expectToken(whileToken, TokenId::WhileKeyword))) {
				goto genBadStmt;
			}

			nextToken();

			Token *lParentheseToken = peekToken();

			if ((syntaxError = expectToken(lParentheseToken, TokenId::LParenthese))) {
				goto genBadStmt;
			}

			nextToken();

			Token *rParentheseToken;
			{
				const TokenId skippingTerminativeToken[] = {
					TokenId::RParenthese,
					TokenId::Semicolon,
					TokenId::RBrace
				};

				if ((syntaxError = parseExpr(0, whileStmt->cond))) {
					if ((syntaxError = lookaheadUntil(std::size(skippingTerminativeToken), skippingTerminativeToken))) {
						goto genBadStmt;
					}
					goto genBadStmt;
				}

				if ((syntaxError = expectToken((rParentheseToken = peekToken()), TokenId::RParenthese))) {
					goto genBadStmt;
				}

				nextToken();
			}

			break;
		}
		case TokenId::LetKeyword: {
			nextToken();

			peff::RcObjectPtr<VarDefStmtNode> stmt;

			if (!(stmt = peff::allocAndConstruct<VarDefStmtNode>(
					  resourceAllocator.get(),
					  ASTNODE_ALIGNMENT,
					  resourceAllocator.get(),
					  mod,
					  peff::DynArray<VarDefEntryPtr>(resourceAllocator.get())))) {
				return genOutOfMemoryError();
			}

			stmtOut = stmt.get();

			if ((syntaxError = parseVarDefs(stmt->varDefEntries))) {
				goto genBadStmt;
			}

			Token *semicolonToken;

			if ((syntaxError = expectToken((semicolonToken = peekToken()), TokenId::Semicolon))) {
				goto genBadStmt;
			}

			nextToken();

			break;
		}
		case TokenId::BreakKeyword: {
			nextToken();

			peff::RcObjectPtr<BreakStmtNode> stmt;

			if (!(stmt = peff::allocAndConstruct<BreakStmtNode>(
					  resourceAllocator.get(),
					  ASTNODE_ALIGNMENT,
					  resourceAllocator.get(),
					  mod))) {
				return genOutOfMemoryError();
			}

			stmtOut = stmt.get();

			Token *semicolonToken;

			if ((syntaxError = expectToken((semicolonToken = peekToken()), TokenId::Semicolon))) {
				goto genBadStmt;
			}

			nextToken();

			break;
		}
		case TokenId::ContinueKeyword: {
			nextToken();

			peff::RcObjectPtr<ContinueStmtNode> stmt;

			if (!(stmt = peff::allocAndConstruct<ContinueStmtNode>(
					  resourceAllocator.get(),
					  ASTNODE_ALIGNMENT,
					  resourceAllocator.get(),
					  mod))) {
				return genOutOfMemoryError();
			}

			stmtOut = stmt.get();

			Token *semicolonToken;

			if ((syntaxError = expectToken((semicolonToken = peekToken()), TokenId::Semicolon))) {
				goto genBadStmt;
			}

			nextToken();

			break;
		}
		case TokenId::ReturnKeyword: {
			nextToken();

			peff::RcObjectPtr<ReturnStmtNode> stmt;

			if (!(stmt = peff::allocAndConstruct<ReturnStmtNode>(
					  resourceAllocator.get(),
					  ASTNODE_ALIGNMENT,
					  resourceAllocator.get(),
					  mod,
					  nullptr))) {
				return genOutOfMemoryError();
			}

			stmtOut = stmt.get();

			nextToken();

			const TokenId skippingTerminativeToken[] = {
				TokenId::RParenthese,
				TokenId::Semicolon,
				TokenId::RBrace
			};

			if ((syntaxError = parseExpr(0, stmt->value))) {
				if ((syntaxError = lookaheadUntil(std::size(skippingTerminativeToken), skippingTerminativeToken))) {
					goto genBadStmt;
				}
				goto genBadStmt;
			}

			break;
		}
		default: {
			Token *currentToken;
			peff::RcObjectPtr<ExprNode> curExpr;

			peff::RcObjectPtr<ExprStmtNode> stmt;

			if(!(stmt = peff::allocAndConstruct<ExprStmtNode>(resourceAllocator.get(), ASTNODE_ALIGNMENT, resourceAllocator.get(), mod))) {
				return genOutOfMemoryError();
			}

			stmtOut = stmt.get();

			for (;;) {
				if ((syntaxError = parseExpr(0, curExpr))) {
					if (!syntaxErrors.pushBack(std::move(syntaxError.value())))
						return genOutOfMemoryError();
					syntaxError.reset();
					goto genBadStmt;
				}

				currentToken = peekToken();

				if (!stmt->exprList.pushBack(std::move(curExpr))) {
					return genOutOfMemoryError();
				}

				if (prefixToken->tokenId != TokenId::Comma)
					break;

				nextToken();
			}

			break;
		}
	}

	return {};

genBadStmt:
	if (!(stmtOut = peff::allocAndConstruct<BadStmtNode>(resourceAllocator.get(), ASTNODE_ALIGNMENT, resourceAllocator.get(), mod, stmtOut.get())))
		return genOutOfMemoryError();
	stmtOut->tokenRange = { prefixToken->index, idxCurrentToken };
	return syntaxError;
}
