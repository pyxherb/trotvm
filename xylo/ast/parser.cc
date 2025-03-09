#include "parser.h"

using namespace xylo;

XYLO_API Parser::Parser(TokenList &&tokenList) : tokenList(std::move(tokenList)) {
}

XYLO_API std::optional<SyntaxError> Parser::parseIdRef(IdRefPtr &idRefOut) {
	for (;;) {

	}
}
