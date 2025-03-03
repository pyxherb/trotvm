#ifndef _XYLO_AST_EXPR_H_
#define _XYLO_AST_EXPR_H_

#include "astnode.h"

namespace xylo {
	enum class ExprKind {
		Unary,	  // Unary operation
		Binary,	  // Binary operation
		Ternary,  // Ternary operation
		IdRef,	  // Identifier Reference

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

		InitializerList,  // Initializer List

		Call,  // Call

		Sizeof,	 // Size of

		Cast,  // Cast

		Wrapper,  // Expression wrapper

		Volatile,  // Volatile expression wrapper

		Bad,  // Bad expression
	};

	enum class UnaryOp {
		LNot,
		Not,
		Neg,
		AddressOf
	};

	enum class BinaryOp {
		Add = 0,
		Sub,
		Mul,
		Div,
		Mod,
		And,
		Or,
		Xor,
		LAnd,
		LOr,
		Shl,
		Shr,

		Assign,
		AssignAdd,
		AssignSub,
		AssignMul,
		AssignDiv,
		AssignMod,
		AssignAnd,
		AssignOr,
		AssignXor,
		AssignShl,
		AssignShr,

		Eq,
		Neq,
		Lt,
		Gt,
		LtEq,
		GtEq,
		Subscript,

		MemberAccess
	};
}

#endif
