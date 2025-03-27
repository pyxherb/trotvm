#ifndef _XYLO_AST_STRUCT_H_
#define _XYLO_AST_STRUCT_H_

#include "var.h"

namespace xylo {
	class StructNode : public MemberNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::HashMap<std::string_view, peff::RcObjectPtr<VarNode>> fields;

		XYLO_API StructNode(peff::Alloc *selfAllocator, Module *mod);
		XYLO_API StructNode(const StructNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~StructNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};
}

#endif
