#ifndef _XYLO_AST_METAEXPR_H_
#define _XYLO_AST_METAEXPR_H_

#include "astnode.h"

namespace xylo {
	enum class MetaExprKind {
		IdRef,	 // Identifier Reference

		I8,		  // i8 Literal
		I16,	  // i16 Literal
		I32,	  // i32 Literal
		I64,	  // i64 Literal
		U8,		  // u8 Literal
		U16,	  // u16 Literal
		U32,	  // u32 Literal
		U64,	  // u64 Literal
		F32,	  // f32 Literal
		F64,	  // f64 Literal
		String,	  // String Literal
		Bool,	  // bool Literal
		Nullptr,  // nullptr

		Call,  // Call
		Assign,		// Assign

		Wrapper,  // Expression wrapper

		Bad,  // Bad expression
	};
}

#endif
