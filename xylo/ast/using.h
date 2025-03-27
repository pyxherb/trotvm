#ifndef _XYLO_AST_USING_H_
#define _XYLO_AST_USING_H_

#include "namespace.h"

namespace xylo {
	class NamespaceNode;

	class UsingNode : public MemberNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::RcObjectPtr<TypeNameNode> sourceType;

		XYLO_API UsingNode(peff::Alloc *selfAllocator, Module *mod);
		XYLO_API UsingNode(const UsingNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~UsingNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};
}

#endif
