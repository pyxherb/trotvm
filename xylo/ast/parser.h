#ifndef _XYLO_AST_PARSER_H_
#define _XYLO_AST_PARSER_H_

#include "lexer.h"
#include "expr.h"
#include "stmt.h"
#include "typename.h"
#include "idref.h"

namespace xylo {
	struct SyntaxError {
		SourceLocation location;
		const char *message;
	};

	class Parser {
	public:
		TokenList tokenList;
		size_t idxPrevToken = 0, idxCurrentToken = 0;

		TROTVM_API Parser(TokenList &&tokenList);

		TROTVM_API Token *nextToken(bool keepNewLine = false, bool keepWhitespace = false, bool keepComment = false);
		TROTVM_API Token *peekToken(bool keepNewLine = false, bool keepWhitespace = false, bool keepComment = false);

		std::optional<SyntaxError> splitRshOpToken();

		std::optional<SyntaxError> parseIdRef(IdRefPtr &idRefOut);
		std::optional<SyntaxError> parseExpr(std::shared_ptr<ExprNode> &exprOut);
		std::optional<SyntaxError> parseStmt(std::shared_ptr<StmtNode> &stmtOut);
		std::optional<SyntaxError> parseTypeName(std::shared_ptr<TypeNameNode> &typeNameOut);

		std::optional<SyntaxError> parseProgramStmt();

		std::optional<SyntaxError> parseProgram();
	};
}

#endif
