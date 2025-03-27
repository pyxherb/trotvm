#include "fn.h"

using namespace xylo;

XYLO_API peff::RcObjectPtr<AstNode> FnNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<FnNode> duplicatedNode(peff::allocAndConstruct<FnNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API FnNode::FnNode(
	peff::Alloc *selfAllocator,
	Module *mod)
	: MemberNode(AstNodeType::Fn, selfAllocator, mod),
	params(selfAllocator) {
}

XYLO_API FnNode::FnNode(const FnNode &rhs, peff::Alloc *allocator, bool &succeededOut) : MemberNode(rhs, allocator, succeededOut), params(allocator) {
	if(!succeededOut) {
		return;
	}
	if(!(body = rhs.body->duplicate<CodeBlockStmtNode>(allocator))) {
		succeededOut = false;
		return;
	}
	for(auto [name, p] : rhs.params) {
		peff::RcObjectPtr<VarNode> dp;
		if(!(dp = p->duplicate<VarNode>(allocator))) {
			succeededOut = false;
			return;
		}

		dp->parent = this;

		if(!(params.insert(dp->name, std::move(dp)))) {
			succeededOut = false;
			return;
		}
	}

	succeededOut = true;
}

XYLO_API FnNode::~FnNode() {
}

XYLO_API void FnNode::onRefZero() noexcept {
	peff::destroyAndRelease<FnNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}