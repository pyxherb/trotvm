#ifndef _XYLO_AST_TYPENAME_BASE_H_
#define _XYLO_AST_TYPENAME_BASE_H_

#include "astnode.h"

namespace xylo {
	enum class TypeNameKind : uint8_t {
		Void = 0,
		I8,
		I16,
		I32,
		I64,
		U8,
		U16,
		U32,
		U64,
		F32,
		F64,
		ISize,
		USize,
		String,
		Bool,
		Custom,
		Expr,

		Array,
		Pointer
	};

	class TypeNameNode : public AstNode {
	public:
		TypeNameKind typeNameKind;

		XYLO_API TypeNameNode(TypeNameKind typeNameKind, peff::Alloc *selfAllocator, Module *mod);
		XYLO_API TypeNameNode(const TypeNameNode &rhs, peff::Alloc *selfAllocator);
		XYLO_API ~TypeNameNode();
	};
}

#endif
