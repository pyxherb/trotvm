#ifndef _XYLO_AST_ATTRIB_H_
#define _XYLO_AST_ATTRIB_H_

#include "expr.h"

namespace xylo {
	class AttributeItemNode : public AstNode {
	public:
		IdRef name;
		peff::DynArray<peff::RcObjectPtr<ExprNode>> fieldData;

		XYLO_API AttributeItemNode(peff::Alloc *allocator, Module *mod);
		XYLO_API virtual ~AttributeItemNode();
	};
}

#endif
