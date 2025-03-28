#include "namespace.h"

using namespace xylo;

XYLO_API MemberNode::MemberNode(
	AstNodeType astNodeType,
	peff::Alloc *selfAllocator,
	Module *mod)
	: AstNode(astNodeType, selfAllocator, mod),
	name(selfAllocator) {
}

XYLO_API MemberNode::MemberNode(const MemberNode &rhs, peff::Alloc *allocator, bool &succeededOut) : AstNode(rhs, allocator), name(allocator) {
	if(!name.build(rhs.name)) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

XYLO_API MemberNode::~MemberNode() {
}

XYLO_API peff::RcObjectPtr<AstNode> NamespaceNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<NamespaceNode> duplicatedNode(peff::allocAndConstruct<NamespaceNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API NamespaceNode::NamespaceNode(
	peff::Alloc *selfAllocator,
	Module *mod)
	: MemberNode(AstNodeType::Namespace, selfAllocator, mod),
	members(selfAllocator) {
}

XYLO_API NamespaceNode::NamespaceNode(const NamespaceNode &rhs, peff::Alloc *allocator, bool &succeededOut) : MemberNode(rhs, allocator, succeededOut), members(allocator) {
	if(!succeededOut) {
		return;
	}
	for(const auto &[name, member] : rhs.members) {
		peff::RcObjectPtr<MemberNode> duplicatedMember;
		if(!(duplicatedMember = member->duplicate<MemberNode>(allocator))) {
			succeededOut = false;
			return;
		}

		duplicatedMember->parent = this;

		if(!(members.insert(duplicatedMember->name, std::move(duplicatedMember)))) {
			succeededOut = false;
			return;
		}
	}

	succeededOut = true;
}

XYLO_API NamespaceNode::~NamespaceNode() {
}

XYLO_API void NamespaceNode::onRefZero() noexcept {
	peff::destroyAndRelease<NamespaceNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API bool NamespaceNode::addMember(MemberNode *memberNode) noexcept {
	if(!members.insert(memberNode->name, peff::RcObjectPtr<MemberNode>(memberNode))) {
		return false;
	}
	return true;
}

XYLO_API void NamespaceNode::removeMember(const std::string_view &name) noexcept {
	members.remove(name);
}