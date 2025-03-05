#ifndef _XYLO_AST_STMT_H_
#define _XYLO_AST_STMT_H_

#include "expr.h"

namespace xylo {
	enum class StmtKind : uint8_t {
		Expr = 0,	// Expression
		VarDef,		// (Local) Variable definition
		Break,		// Break
		Continue,	// Continue
		For,		// For
		ForEach,	// For each
		While,		// While
		Return,		// Return
		If,			// If
		Switch,		// Switch
		CodeBlock,	// Code block
		Goto,		// Goto

		Bad,  // Bad statement - unrecognized statement type
	};

	class StmtNode : public AstNode {
	public:
		StmtKind stmtKind;

		XYLO_API StmtNode(StmtKind stmtKind, peff::Alloc *selfAllocator);
		XYLO_API StmtNode(const StmtNode &rhs);
		XYLO_API ~StmtNode();
	};

	class ExprStmtNode : public StmtNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::RcObjectPtr<ExprNode> expr;

		XYLO_API ExprStmtNode(peff::Alloc *selfAllocator, ExprNode *expr);
		XYLO_API ExprStmtNode(const ExprStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~ExprStmtNode();
	};

	class VarDefEntry {
	public:
		peff::RcObjectPtr<peff::Alloc> selfAllocator;
		peff::String name;
		peff::RcObjectPtr<TypeNameNode> type;
		peff::RcObjectPtr<ExprNode> initialValue;

		XYLO_API VarDefEntry(peff::Alloc *selfAllocator, peff::String &&name, TypeNameNode *type, ExprNode *initialValue);
		XYLO_API ~VarDefEntry();

		XYLO_API void dealloc() noexcept;
	};

	using VarDefEntryPtr = std::unique_ptr<VarDefEntry, peff::DeallocableDeleter<VarDefEntry>>;

	XYLO_API VarDefEntryPtr duplicateVarDefEntry(VarDefEntry *varDefEntry, peff::Alloc *allocator);

	class VarDefStmtNode : public StmtNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::DynArray<VarDefEntryPtr> varDefEntries;

		XYLO_API VarDefStmtNode(peff::Alloc *selfAllocator, peff::DynArray<VarDefEntry> &&varDefEntries);
		XYLO_API VarDefStmtNode(const VarDefStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~VarDefStmtNode();
	};
}

#endif
