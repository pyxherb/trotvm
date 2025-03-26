#ifndef _XYLO_AST_EXPR_H_
#define _XYLO_AST_EXPR_H_

#include "typename.h"
#include <peff/containers/hashmap.h>

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

		InitializerList,	   // Initializer list
		DesignatedInitializer,  // Specified initializer

		Call,		// Call
		MacroCall,	// Macro call

		Cast,  // Cast

		Wrapper,  // Expression wrapper

		Volatile,  // Volatile expression wrapper

		TypeName,  // Type name

		Bad,  // Bad expression
	};

	enum class UnaryOp {
		LNot,
		Not,
		Neg,
		AddressOf,
		Dereference,
		Sizeof
	};

	class ExprNode : public AstNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		ExprKind exprKind;

		XYLO_API ExprNode(ExprKind exprKind, peff::Alloc *selfAllocator, Module *mod);
		XYLO_API ExprNode(const ExprNode &rhs, peff::Alloc *allocator);
		XYLO_API ~ExprNode();
	};

	class UnaryExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		UnaryOp unaryOp;
		peff::RcObjectPtr<ExprNode> operand;

		XYLO_API UnaryExprNode(peff::Alloc *selfAllocator, Module *mod, UnaryOp unaryOp, ExprNode *operand);
		XYLO_API UnaryExprNode(const UnaryExprNode &rhs, peff::Alloc *selfAllocator, bool &succeededOut);
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
		AddAssign,
		SubAssign,
		MulAssign,
		DivAssign,
		ModAssign,
		AndAssign,
		OrAssign,
		XorAssign,
		ShlAssign,
		ShrAssign,

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
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		BinaryOp binaryOp;
		peff::RcObjectPtr<ExprNode> lhs, rhs;

		XYLO_API BinaryExprNode(peff::Alloc *selfAllocator, Module *mod, BinaryOp binaryOp, ExprNode *lhs, ExprNode *rhs);
		XYLO_API BinaryExprNode(const BinaryExprNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~BinaryExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class TernaryExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::RcObjectPtr<ExprNode> cond, lhs, rhs;

		XYLO_API TernaryExprNode(peff::Alloc *selfAllocator, Module *mod, ExprNode *cond, ExprNode *lhs, ExprNode *rhs);
		XYLO_API TernaryExprNode(const TernaryExprNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~TernaryExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class IdRefExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		IdRefPtr idRefPtr;

		XYLO_API IdRefExprNode(peff::Alloc *selfAllocator, Module *mod, IdRefPtr &&idRefPtr);
		XYLO_API IdRefExprNode(const IdRefExprNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~IdRefExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class HeadedIdRefExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::RcObjectPtr<ExprNode> head;
		IdRefPtr idRefPtr;

		XYLO_API HeadedIdRefExprNode(peff::Alloc *selfAllocator, Module *mod, ExprNode *head, IdRefPtr &&idRefPtr);
		XYLO_API HeadedIdRefExprNode(const HeadedIdRefExprNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~HeadedIdRefExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class I8LiteralExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		int8_t data;

		XYLO_API I8LiteralExprNode(peff::Alloc *selfAllocator, Module *mod, int8_t data);
		XYLO_API I8LiteralExprNode(const I8LiteralExprNode &rhs, peff::Alloc *allocator);
		XYLO_API ~I8LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class I16LiteralExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		int16_t data;

		XYLO_API I16LiteralExprNode(peff::Alloc *selfAllocator, Module *mod, int16_t data);
		XYLO_API I16LiteralExprNode(const I16LiteralExprNode &rhs, peff::Alloc *allocator);
		XYLO_API ~I16LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class I32LiteralExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		int32_t data;

		XYLO_API I32LiteralExprNode(peff::Alloc *selfAllocator, Module *mod, int32_t data);
		XYLO_API I32LiteralExprNode(const I32LiteralExprNode &rhs, peff::Alloc *allocator);
		XYLO_API ~I32LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class I64LiteralExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		int64_t data;

		XYLO_API I64LiteralExprNode(peff::Alloc *selfAllocator, Module *mod, int64_t data);
		XYLO_API I64LiteralExprNode(const I64LiteralExprNode &rhs, peff::Alloc *allocator);
		XYLO_API ~I64LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class U8LiteralExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		uint8_t data;

		XYLO_API U8LiteralExprNode(peff::Alloc *selfAllocator, Module *mod, uint8_t data);
		XYLO_API U8LiteralExprNode(const U8LiteralExprNode &rhs, peff::Alloc *allocator);
		XYLO_API ~U8LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class U16LiteralExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		uint16_t data;

		XYLO_API U16LiteralExprNode(peff::Alloc *selfAllocator, Module *mod, uint16_t data);
		XYLO_API U16LiteralExprNode(const U16LiteralExprNode &rhs, peff::Alloc *allocator);
		XYLO_API ~U16LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class U32LiteralExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		uint32_t data;

		XYLO_API U32LiteralExprNode(peff::Alloc *selfAllocator, Module *mod, uint32_t data);
		XYLO_API U32LiteralExprNode(const U32LiteralExprNode &rhs, peff::Alloc *allocator);
		XYLO_API ~U32LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class U64LiteralExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		uint64_t data;

		XYLO_API U64LiteralExprNode(peff::Alloc *selfAllocator, Module *mod, uint64_t data);
		XYLO_API U64LiteralExprNode(const U64LiteralExprNode &rhs, peff::Alloc *allocator);
		XYLO_API ~U64LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class F32LiteralExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		float data;

		XYLO_API F32LiteralExprNode(peff::Alloc *selfAllocator, Module *mod, float data);
		XYLO_API F32LiteralExprNode(const F32LiteralExprNode &rhs, peff::Alloc *allocator);
		XYLO_API ~F32LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class F64LiteralExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		double data;

		XYLO_API F64LiteralExprNode(peff::Alloc *selfAllocator, Module *mod, double data);
		XYLO_API F64LiteralExprNode(const F64LiteralExprNode &rhs, peff::Alloc *allocator);
		XYLO_API ~F64LiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class BoolLiteralExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		bool data;

		XYLO_API BoolLiteralExprNode(peff::Alloc *selfAllocator, Module *mod, bool data);
		XYLO_API BoolLiteralExprNode(const BoolLiteralExprNode &rhs, peff::Alloc *allocator);
		XYLO_API ~BoolLiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class StringLiteralExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::String data;

		XYLO_API StringLiteralExprNode(peff::Alloc *selfAllocator, Module *mod, peff::String &&data);
		XYLO_API StringLiteralExprNode(const StringLiteralExprNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~StringLiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class NullptrLiteralExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		XYLO_API NullptrLiteralExprNode(peff::Alloc *selfAllocator, Module *mod);
		XYLO_API NullptrLiteralExprNode(const NullptrLiteralExprNode &rhs, peff::Alloc *allocator);
		XYLO_API ~NullptrLiteralExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class InitializerListExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::DynArray<peff::RcObjectPtr<ExprNode>> elements;

		XYLO_API InitializerListExprNode(peff::Alloc *selfAllocator, Module *mod);
		XYLO_API InitializerListExprNode(const InitializerListExprNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~InitializerListExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class DesignatedInitializerExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::DynArray<std::pair<peff::String, peff::RcObjectPtr<ExprNode>>> fields;

		XYLO_API DesignatedInitializerExprNode(peff::Alloc *selfAllocator, Module *mod);
		XYLO_API DesignatedInitializerExprNode(const DesignatedInitializerExprNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~DesignatedInitializerExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class CallExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::RcObjectPtr<ExprNode> target;
		peff::DynArray<peff::RcObjectPtr<ExprNode>> args;
		peff::DynArray<size_t> idxCommaTokens;
		bool isAsync = false;
		size_t lParentheseTokenIndex = SIZE_MAX, rParentheseTokenIndex = SIZE_MAX, asyncKeywordTokenIndex = SIZE_MAX;

		XYLO_API CallExprNode(peff::Alloc *selfAllocator, Module *mod, ExprNode *target, peff::DynArray<peff::RcObjectPtr<ExprNode>> &&args);
		XYLO_API CallExprNode(const CallExprNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~CallExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class MacroCallExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		IdRefPtr target;
		peff::DynArray<peff::RcObjectPtr<ExprNode>> args;

		XYLO_API MacroCallExprNode(peff::Alloc *selfAllocator, Module *mod, IdRefPtr &&target, peff::DynArray<peff::RcObjectPtr<ExprNode>> &&args);
		XYLO_API MacroCallExprNode(const MacroCallExprNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~MacroCallExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class CastExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::RcObjectPtr<TypeNameNode> targetType;
		peff::RcObjectPtr<ExprNode> source;
		size_t asKeywordTokenIndex = SIZE_MAX;

		XYLO_API CastExprNode(peff::Alloc *selfAllocator, Module *mod, TypeNameNode *targetType, ExprNode *source);
		XYLO_API CastExprNode(const CastExprNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~CastExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class WrapperExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::RcObjectPtr<ExprNode> target;

		XYLO_API WrapperExprNode(peff::Alloc *selfAllocator, Module *mod, ExprNode *target);
		XYLO_API WrapperExprNode(const WrapperExprNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~WrapperExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class VolatileExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::RcObjectPtr<ExprNode> target;

		XYLO_API VolatileExprNode(peff::Alloc *selfAllocator, Module *mod, ExprNode *target);
		XYLO_API VolatileExprNode(const VolatileExprNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~VolatileExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class TypeNameExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::RcObjectPtr<TypeNameNode> type;
		size_t typeNameTokenIndex = SIZE_MAX;

		XYLO_API TypeNameExprNode(peff::Alloc *selfAllocator, Module *mod, TypeNameNode *type);
		XYLO_API TypeNameExprNode(const TypeNameExprNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~TypeNameExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class BadExprNode : public ExprNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::RcObjectPtr<ExprNode> incompleteExpr;

		XYLO_API BadExprNode(peff::Alloc *selfAllocator, Module *mod, ExprNode *incompleteExpr);
		XYLO_API BadExprNode(const BadExprNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~BadExprNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};
}

#endif
