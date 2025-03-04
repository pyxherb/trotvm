#include "astnode.h"

using namespace xylo;

XYLO_API AstNode::AstNode(AstNodeType astNodeType, peff::Alloc *selfAllocator) : astNodeType(astNodeType), selfAllocator(selfAllocator) {
}

XYLO_API AstNode::~AstNode() {
}

XYLO_API peff::RcObjectPtr<AstNode> AstNode::doDuplicate(peff::Alloc *newAllocator) const {
	std::terminate();
}
