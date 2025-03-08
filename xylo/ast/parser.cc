#include "parser.h"

using namespace xylo;

TROTVM_API Parser::Parser(TokenList &&tokenList) : tokenList(std::move(tokenList)) {
}
