#include "astnode.h"

using namespace kast;

KAST_API AstNode::AstNode(AstNodeType astNodeType) : astNodeType(astNodeType) {
}

KAST_API AstNode::~AstNode() {
}
