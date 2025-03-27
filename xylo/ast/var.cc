#include "var.h"

using namespace xylo;

XYLO_API peff::RcObjectPtr<AstNode> VarNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<VarNode> duplicatedNode(peff::allocAndConstruct<VarNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API VarNode::VarNode(
	peff::Alloc *selfAllocator,
	Module *mod)
	: MemberNode(AstNodeType::Var, selfAllocator, mod) {
}

XYLO_API VarNode::VarNode(const VarNode &rhs, peff::Alloc *allocator, bool &succeededOut) : MemberNode(rhs, allocator, succeededOut) {
	if (!succeededOut) {
		return;
	}

	if (!(type = rhs.type->duplicate<TypeNameNode>(allocator))) {
		succeededOut = false;
		return;
	}

	if (!(initialValue = rhs.initialValue->duplicate<ExprNode>(allocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

XYLO_API VarNode::~VarNode() {
}

XYLO_API void VarNode::onRefZero() noexcept {
	peff::destroyAndRelease<VarNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}