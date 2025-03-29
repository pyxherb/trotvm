#include "struct.h"

using namespace xylo;

XYLO_API peff::RcObjectPtr<AstNode> StructNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<StructNode> duplicatedNode(peff::allocAndConstruct<StructNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API StructNode::StructNode(
	peff::Alloc *selfAllocator,
	Module *mod)
	: MemberNode(AstNodeType::Struct, selfAllocator, mod),
	fields(selfAllocator) {
}

XYLO_API StructNode::StructNode(const StructNode &rhs, peff::Alloc *allocator, bool &succeededOut) : MemberNode(rhs, allocator, succeededOut), fields(allocator) {
	if(!succeededOut) {
		return;
	}
	for(auto [name, f] : rhs.fields) {
		peff::RcObjectPtr<VarNode> df;
		if(!(df = f->duplicate<VarNode>(allocator))) {
			succeededOut = false;
			return;
		}

		df->parent = this;

		if(!(fields.insert(df->name, std::move(df)))) {
			succeededOut = false;
			return;
		}
	}

	succeededOut = true;
}

XYLO_API StructNode::~StructNode() {
}

XYLO_API void StructNode::onRefZero() noexcept {
	peff::destroyAndRelease<StructNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}
