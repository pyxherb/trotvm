#include "../parser.h"

using namespace xylo;

TROTVM_API Token *Parser::nextToken(bool keepNewLine, bool keepWhitespace, bool keepComment) {
	size_t &i = idxCurrentToken;

	while (i < tokenList.size()) {
		Token *currentToken = tokenList.at(i).get();
		currentToken->index = i;

		switch (tokenList.at(i)->tokenId) {
			case TokenId::NewLine:
				if (keepNewLine) {
					idxPrevToken = idxCurrentToken;
					++i;
					return currentToken;
				}
				break;
			case TokenId::Whitespace:
				if (keepWhitespace) {
					idxPrevToken = idxCurrentToken;
					++i;
					return currentToken;
				}
				break;
			case TokenId::LineComment:
			case TokenId::BlockComment:
			case TokenId::DocumentationComment:
				if (keepComment) {
					idxPrevToken = idxCurrentToken;
					++i;
					return currentToken;
				}
				break;
			default:
				idxPrevToken = idxCurrentToken;
				++i;
				return currentToken;
		}

		++i;
	}

	return tokenList.back().get();
}

TROTVM_API Token *Parser::peekToken(bool keepNewLine, bool keepWhitespace, bool keepComment) {
	size_t i = idxCurrentToken;

	while (i < tokenList.size()) {
		Token *currentToken = tokenList.at(i).get();
		currentToken->index = i;

		switch (currentToken->tokenId) {
			case TokenId::NewLine:
				if (keepNewLine)
					return currentToken;
				break;
			case TokenId::Whitespace:
				if (keepWhitespace)
					return currentToken;
				break;
			case TokenId::LineComment:
			case TokenId::BlockComment:
			case TokenId::DocumentationComment:
				if (keepComment)
					return currentToken;
				break;
			default:
				return currentToken;
		}

		++i;
	}

	return tokenList.back().get();
}

std::optional<SyntaxError> Parser::splitRshOpToken() {
	switch (Token *token = peekToken(); token->tokenId) {
		case TokenId::RshOp: {
			token->tokenId = TokenId::GtOp;
			token->sourceText = token->sourceText.substr(0, 1);
			token->sourceLocation.endPosition.column -= 1;

			OwnedTokenPtr extraClosingToken;
			if (!(extraClosingToken = OwnedTokenPtr(peff::allocAndConstruct<Token>(token->allocator.get(), sizeof(std::max_align_t), token->allocator.get())))) {
				return SyntaxError{
					SourceLocation{ { 0, 0 }, { 0, 0 } },
					"Out of memory"
				};
			}

			extraClosingToken->tokenId = TokenId::GtOp;
			extraClosingToken->sourceLocation =
				SourceLocation{
					SourcePosition{ token->sourceLocation.beginPosition.line, token->sourceLocation.beginPosition.column + 1 },
					token->sourceLocation.endPosition
				};
			extraClosingToken->sourceText = token->sourceText.substr(1);

			if(!tokenList.insert(idxCurrentToken + 1, std::move(extraClosingToken))) {
				return SyntaxError{
					SourceLocation{ { 0, 0 }, { 0, 0 } },
					"Out of memory"
				};
			}

			break;
		}
		default:;
	}

	return {};
}
