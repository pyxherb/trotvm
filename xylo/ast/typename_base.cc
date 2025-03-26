#include "typename_base.h"

using namespace xylo;

XYLO_API TypeNameNode::TypeNameNode(TypeNameKind typeNameKind, peff::Alloc *selfAllocator, Module *mod) : AstNode(AstNodeType::TypeName, selfAllocator, mod), typeNameKind(typeNameKind) {
}

XYLO_API TypeNameNode::TypeNameNode(const TypeNameNode &rhs, peff::Alloc *selfAllocator) : AstNode(rhs, selfAllocator), typeNameKind(rhs.typeNameKind) {
}

XYLO_API TypeNameNode::~TypeNameNode() {
}
