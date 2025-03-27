#ifndef _XYLO_AST_NAMESPACE_H_
#define _XYLO_AST_NAMESPACE_H_

#include "expr.h"

namespace xylo {
	class NamespaceNode;

	class MemberNode : public AstNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::WeakRcObjectPtr<NamespaceNode> parent;
		peff::String name;

		XYLO_API MemberNode(AstNodeType astNodeType, peff::Alloc *selfAllocator, Module *mod);
		XYLO_API MemberNode(const MemberNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~MemberNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class NamespaceNode : public AstNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::HashMap<std::string_view, peff::RcObjectPtr<MemberNode>> members;

		XYLO_API NamespaceNode(peff::Alloc *selfAllocator, Module *mod);
		XYLO_API NamespaceNode(const NamespaceNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~NamespaceNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};
}

#endif
