#ifndef _XYLO_AST_EXPR_H_
#define _XYLO_AST_EXPR_H_

#include "typename.h"

namespace xylo {
	enum class ExprKind {
		Unary,	  // Unary operation
		Binary,	  // Binary operation
		Ternary,  // Ternary operation
		IdRef,	  // Identifier reference

		I8,		  // i8 literal
		I16,	  // i16 literal
		I32,	  // i32 literal
		I64,	  // i64 literal
		U8,		  // u8 literal
		U16,	  // u16 literal
		U32,	  // u32 literal
		U64,	  // u64 literal
		F32,	  // f32 literal
		F64,	  // f64 literal
		String,	  // String literal
		Bool,	  // bool literal
		Nullptr,  // nullptr

		InitializerList,  // Initializer list

		Call,		// Call
		MacroCall,	// Macro call

		Sizeof,	 // Size of

		Move,  // Move

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

	class ExprNode : public AstNode {
	public:
		ExprKind exprKind;

		XYLO_API ExprNode(ExprKind exprKind, peff::Alloc *selfAllocator);
		XYLO_API ExprNode(const ExprNode &rhs);
		XYLO_API ~ExprNode();
	};

	class UnaryExprNode : public ExprNode {
	public:
		UnaryOp unaryOp;
		peff::RcObjectPtr<ExprNode> operand;

		XYLO_API UnaryExprNode(peff::Alloc *selfAllocator, UnaryOp unaryOp, ExprNode *operand);
		XYLO_API ~UnaryExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
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

	class BinaryExprNode : public ExprNode {
	public:
		BinaryOp binaryOp;
		peff::RcObjectPtr<ExprNode> lhs, rhs;

		XYLO_API BinaryExprNode(peff::Alloc *selfAllocator, BinaryOp binaryOp, ExprNode *lhs, ExprNode *rhs);
		XYLO_API ~BinaryExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class TernaryExprNode : public ExprNode {
	public:
		peff::RcObjectPtr<ExprNode> cond, lhs, rhs;

		XYLO_API TernaryExprNode(peff::Alloc *selfAllocator, ExprNode *cond, ExprNode *lhs, ExprNode *rhs);
		XYLO_API ~TernaryExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class IdRefExprNode : public ExprNode {
	public:
		IdRefPtr idRefPtr;

		XYLO_API IdRefExprNode(peff::Alloc *selfAllocator, IdRefPtr &&idRefPtr);
		XYLO_API ~IdRefExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class I8LiteralExprNode : public ExprNode {
	public:
		int8_t data;

		XYLO_API I8LiteralExprNode(peff::Alloc *selfAllocator, int8_t data);
		XYLO_API ~I8LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class I16LiteralExprNode : public ExprNode {
	public:
		int16_t data;

		XYLO_API I16LiteralExprNode(peff::Alloc *selfAllocator, int16_t data);
		XYLO_API ~I16LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class I32LiteralExprNode : public ExprNode {
	public:
		int32_t data;

		XYLO_API I32LiteralExprNode(peff::Alloc *selfAllocator, int32_t data);
		XYLO_API ~I32LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class I64LiteralExprNode : public ExprNode {
	public:
		int64_t data;

		XYLO_API I64LiteralExprNode(peff::Alloc *selfAllocator, int64_t data);
		XYLO_API ~I64LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class U8LiteralExprNode : public ExprNode {
	public:
		uint8_t data;

		XYLO_API U8LiteralExprNode(peff::Alloc *selfAllocator, uint8_t data);
		XYLO_API ~U8LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class U16LiteralExprNode : public ExprNode {
	public:
		uint16_t data;

		XYLO_API U16LiteralExprNode(peff::Alloc *selfAllocator, uint16_t data);
		XYLO_API ~U16LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class U32LiteralExprNode : public ExprNode {
	public:
		uint32_t data;

		XYLO_API U32LiteralExprNode(peff::Alloc *selfAllocator, uint32_t data);
		XYLO_API ~U32LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class U64LiteralExprNode : public ExprNode {
	public:
		uint64_t data;

		XYLO_API U64LiteralExprNode(peff::Alloc *selfAllocator, uint64_t data);
		XYLO_API ~U64LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class F32LiteralExprNode : public ExprNode {
	public:
		float data;

		XYLO_API F32LiteralExprNode(peff::Alloc *selfAllocator, float data);
		XYLO_API ~F32LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class F64LiteralExprNode : public ExprNode {
	public:
		double data;

		XYLO_API F64LiteralExprNode(peff::Alloc *selfAllocator, double data);
		XYLO_API ~F64LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class BoolLiteralExprNode : public ExprNode {
	public:
		bool data;

		XYLO_API BoolLiteralExprNode(peff::Alloc *selfAllocator, bool data);
		XYLO_API ~BoolLiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class StringLiteralExprNode : public ExprNode {
	public:
		peff::String data;

		XYLO_API StringLiteralExprNode(peff::Alloc *selfAllocator, peff::String &&data);
		XYLO_API ~StringLiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class NullptrLiteralExprNode : public ExprNode {
	public:
		XYLO_API NullptrLiteralExprNode(peff::Alloc *selfAllocator);
		XYLO_API ~NullptrLiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class InitializerListExprNode : public ExprNode {
	public:
		peff::DynArray<peff::RcObjectPtr<ExprNode>> elements;

		XYLO_API InitializerListExprNode(peff::Alloc *selfAllocator, peff::DynArray<peff::RcObjectPtr<ExprNode>> &&elements);
		XYLO_API ~InitializerListExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class CallExprNode : public ExprNode {
	public:
		peff::RcObjectPtr<ExprNode> target;
		peff::DynArray<peff::RcObjectPtr<ExprNode>> args;

		XYLO_API CallExprNode(peff::Alloc *selfAllocator, ExprNode *target, peff::DynArray<peff::RcObjectPtr<ExprNode>> &&args);
		XYLO_API ~CallExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class MacroCallExprNode : public ExprNode {
	public:
		IdRefPtr target;
		peff::DynArray<peff::RcObjectPtr<ExprNode>> args;

		XYLO_API MacroCallExprNode(peff::Alloc *selfAllocator, IdRefPtr &&target, peff::DynArray<peff::RcObjectPtr<ExprNode>> &&args);
		XYLO_API ~MacroCallExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	enum class MetaExprKind {
		Regular = 0,

		TypeName,  // Type name
	};
}

#endif
