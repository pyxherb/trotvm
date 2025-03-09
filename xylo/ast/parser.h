#ifndef _XYLO_AST_PARSER_H_
#define _XYLO_AST_PARSER_H_

#include "lexer.h"
#include "expr.h"
#include "stmt.h"
#include "typename.h"
#include "idref.h"

namespace xylo {
	enum class SyntaxErrorKind {
		OutOfMemory,
		UnexpectedToken,
		ExpectingTokens
	};

	struct ExpectingTokensErrorExData {
		peff::Set<TokenId> expectingTokenIds;

		XYLO_FORCEINLINE ExpectingTokensErrorExData(peff::Alloc *allocator) : expectingTokenIds(allocator) {
		}
	};

	struct SyntaxError {
		TokenRange tokenRange;
		SyntaxErrorKind errorKind;
		std::variant<std::monostate, ExpectingTokensErrorExData> exData;

		XYLO_FORCEINLINE SyntaxError(
			const TokenRange &tokenRange,
			SyntaxErrorKind errorKind)
			: tokenRange(tokenRange),
			  errorKind(errorKind) {
		}

		XYLO_FORCEINLINE SyntaxError(
			const TokenRange &tokenRange,
			ExpectingTokensErrorExData &&exData)
			: tokenRange(tokenRange),
			  errorKind(SyntaxErrorKind::ExpectingTokens),
			  exData(std::move(exData)) {
		}

		XYLO_FORCEINLINE ExpectingTokensErrorExData &getExpectingTokensErrorExData() {
			return std::get<ExpectingTokensErrorExData>(exData);
		}

		XYLO_FORCEINLINE const ExpectingTokensErrorExData &getExpectingTokensErrorExData() const {
			return std::get<ExpectingTokensErrorExData>(exData);
		}
	};

	class Parser {
	public:
		peff::RcObjectPtr<peff::Alloc> selfAllocator;
		TokenList tokenList;
		size_t idxPrevToken = 0, idxCurrentToken = 0;

		XYLO_API Parser(TokenList &&tokenList);

		XYLO_API Token *nextToken(bool keepNewLine = false, bool keepWhitespace = false, bool keepComment = false);
		XYLO_API Token *peekToken(bool keepNewLine = false, bool keepWhitespace = false, bool keepComment = false);

		XYLO_FORCEINLINE [[nodiscard]] std::optional<SyntaxError> expectToken(Token *token, TokenId tokenId) {
			if (token->tokenId != tokenId) {
				ExpectingTokensErrorExData exData(selfAllocator.get());
				TokenId copiedTokenId = tokenId;

				if (!exData.expectingTokenIds.insert(std::move(copiedTokenId)))
					return SyntaxError(TokenRange{}, SyntaxErrorKind::OutOfMemory);

				return SyntaxError(TokenRange{ token->index }, std::move(exData));
			}

			return {};
		}

		XYLO_API [[nodiscard]] std::optional<SyntaxError> splitRshOpToken();

		XYLO_API [[nodiscard]] std::optional<SyntaxError> parseIdRef(IdRefPtr &idRefOut);
		XYLO_API [[nodiscard]] std::optional<SyntaxError> parseExpr(ExprNode *&exprOut);
		XYLO_API [[nodiscard]] std::optional<SyntaxError> parseStmt(StmtNode *&stmtOut);
		XYLO_API [[nodiscard]] std::optional<SyntaxError> parseTypeName(TypeNameNode *&typeNameOut);

		XYLO_API [[nodiscard]] std::optional<SyntaxError> parseProgramStmt();

		XYLO_API [[nodiscard]] std::optional<SyntaxError> parseProgram();
	};
}

#endif
