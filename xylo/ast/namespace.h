#ifndef _XYLO_AST_NAMESPACE_H_
#define _XYLO_AST_NAMESPACE_H_

#include "expr.h"

namespace xylo {
	class MemberNode : public AstNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::WeakRcObjectPtr<AstNode> parent;
		peff::String name;

		XYLO_API MemberNode(AstNodeType astNodeType, peff::Alloc *selfAllocator, Module *mod);
		XYLO_API MemberNode(const MemberNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~MemberNode();
	};

	class NamespaceNode : public MemberNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::HashMap<std::string_view, peff::RcObjectPtr<MemberNode>> members;

		XYLO_API NamespaceNode(peff::Alloc *selfAllocator, Module *mod);
		XYLO_API NamespaceNode(const NamespaceNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~NamespaceNode();

		XYLO_API virtual void onRefZero() noexcept override;

		[[nodiscard]] XYLO_API bool addMember(MemberNode *memberNode) noexcept;
		XYLO_API void removeMember(const std::string_view &name) noexcept;
	};
}

#endif
