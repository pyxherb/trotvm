#include "typename_base.h"

using namespace xylo;

XYLO_API TypeNameNode::TypeNameNode(TypeNameKind typeNameKind, peff::Alloc *selfAllocator) : AstNode(AstNodeType::TypeName, selfAllocator), typeNameKind(typeNameKind) {
}

XYLO_API TypeNameNode::TypeNameNode(const TypeNameNode &rhs) : AstNode(rhs), typeNameKind(rhs.typeNameKind) {
}

XYLO_API TypeNameNode::~TypeNameNode() {
}
