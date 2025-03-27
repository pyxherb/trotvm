#include "using.h"

using namespace xylo;

XYLO_API peff::RcObjectPtr<AstNode> UsingNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<UsingNode> duplicatedNode(peff::allocAndConstruct<UsingNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API UsingNode::UsingNode(
	peff::Alloc *selfAllocator,
	Module *mod)
	: MemberNode(AstNodeType::Using, selfAllocator, mod) {
}

XYLO_API UsingNode::UsingNode(const UsingNode &rhs, peff::Alloc *allocator, bool &succeededOut) : MemberNode(rhs, allocator, succeededOut) {
	if (!succeededOut) {
		return;
	}

	if (!(sourceType = rhs.sourceType->duplicate<TypeNameNode>(allocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

XYLO_API UsingNode::~UsingNode() {
}

XYLO_API void UsingNode::onRefZero() noexcept {
	peff::destroyAndRelease<UsingNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}