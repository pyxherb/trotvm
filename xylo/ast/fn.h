#ifndef _XYLO_AST_STRUCT_H_
#define _XYLO_AST_STRUCT_H_

#include "var.h"
#include "stmt.h"

namespace xylo {
	using FnFlags = uint32_t;

	class FnNode : public MemberNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::HashMap<std::string_view, peff::RcObjectPtr<VarNode>> params;
		peff::RcObjectPtr<CodeBlockStmtNode> body;
		FnFlags fnFlags = 0;

		XYLO_API FnNode(peff::Alloc *selfAllocator, Module *mod);
		XYLO_API FnNode(const FnNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~FnNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};
}

#endif
