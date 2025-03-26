#include "../parser.h"

using namespace xylo;

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

			if(elseToken->tokenId == TokenId::ElseKeyword) {
				nextToken();

				if ((syntaxError = parseStmt(ifStmt->falseBody))) {
					goto genBadStmt;
				}
			}

			break;
		}
		default:
			nextToken();
			return SyntaxError(
				TokenRange{ prefixToken->index },
				SyntaxErrorKind::ExpectingStmt);
	}

	return {};

genBadStmt:
	if (!(stmtOut = peff::allocAndConstruct<BadStmtNode>(resourceAllocator.get(), ASTNODE_ALIGNMENT, resourceAllocator.get(), mod, stmtOut.get())))
		return genOutOfMemoryError();
	stmtOut->tokenRange = { prefixToken->index, idxCurrentToken };
	return syntaxError;
}
