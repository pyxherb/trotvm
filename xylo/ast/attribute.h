#ifndef _XYLO_AST_ATTRIBUTE_H_
#define _XYLO_AST_ATTRIBUTE_H_

#include "var.h"

namespace xylo {
	class AttributeDef : public MemberNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::DynArray<peff::RcObjectPtr<VarNode>> fields;
		peff::HashMap<std::string_view, size_t> fieldIndices;

		XYLO_API AttributeDef(peff::Alloc *allocator, Module *mod);
		XYLO_API AttributeDef(const AttributeDef &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API virtual ~AttributeDef();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class AttributeNode : public MemberNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::DynArray<peff::RcObjectPtr<ExprNode>> fieldData;

		XYLO_API AttributeNode(peff::Alloc *allocator, Module *mod);
		XYLO_API AttributeNode(const AttributeNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API virtual ~AttributeNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};
}

#endif
