#ifndef _XYLO_AST_VAR_H_
#define _XYLO_AST_VAR_H_

#include "namespace.h"

namespace xylo {
	class NamespaceNode;

	class VarNode : public MemberNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::RcObjectPtr<TypeNameNode> type;
		peff::RcObjectPtr<ExprNode> initialValue;

		XYLO_API VarNode(peff::Alloc *selfAllocator, Module *mod);
		XYLO_API VarNode(const VarNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~VarNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};
}

#endif
