#ifndef _XYLO_AST_STMT_H_
#define _XYLO_AST_STMT_H_

#include "expr.h"

namespace xylo {
	enum class StmtKind : uint8_t {
		Expr = 0,  // Expression
		VarDef,	   // (Local) Variable definition
		Break,	   // Break
		Continue,  // Continue
		For,	   // For
		ForEach,   // For each
		While,	   // While
		Return,	   // Return
		If,		   // If
		Switch,		// Switch
		CodeBlock,	// Code block
		Goto,		// Goto

		Bad,  // Bad statement - unrecognized statement type
	};

	class StmtNode : public AstNode {
	public:
		StmtKind stmtKind;

		XYLO_API StmtNode(StmtKind stmtKind, peff::Alloc *selfAllocator, Module *mod);
		XYLO_API StmtNode(const StmtNode &rhs);
		XYLO_API ~StmtNode();
	};

	class ExprStmtNode : public StmtNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::RcObjectPtr<ExprNode> expr;

		XYLO_API ExprStmtNode(peff::Alloc *selfAllocator, Module *mod, ExprNode *expr);
		XYLO_API ExprStmtNode(const ExprStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~ExprStmtNode();

		XYLO_API virtual void onRefZero() noexcept override;
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

		XYLO_API VarDefStmtNode(peff::Alloc *selfAllocator, Module *mod, peff::DynArray<VarDefEntryPtr> &&varDefEntries);
		XYLO_API VarDefStmtNode(const VarDefStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~VarDefStmtNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class BreakStmtNode : public StmtNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		XYLO_API BreakStmtNode(peff::Alloc *selfAllocator, Module *mod);
		XYLO_API BreakStmtNode(const BreakStmtNode &rhs);
		XYLO_API ~BreakStmtNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class ContinueStmtNode : public StmtNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		XYLO_API ContinueStmtNode(peff::Alloc *selfAllocator, Module *mod);
		XYLO_API ContinueStmtNode(const ContinueStmtNode &rhs);
		XYLO_API ~ContinueStmtNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class ForStmtNode : public StmtNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::DynArray<VarDefEntryPtr> varDefEntries;
		peff::RcObjectPtr<ExprNode> cond, step;
		peff::RcObjectPtr<StmtNode> body;

		XYLO_API ForStmtNode(peff::Alloc *selfAllocator, Module *mod, peff::DynArray<VarDefEntryPtr> &&varDefEntries, ExprNode *cond, ExprNode *step, StmtNode *body);
		XYLO_API ForStmtNode(const ForStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~ForStmtNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class ForEachStmtNode : public StmtNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::String varName;
		peff::RcObjectPtr<ExprNode> cond;
		peff::RcObjectPtr<StmtNode> body;

		XYLO_API ForEachStmtNode(peff::Alloc *selfAllocator, Module *mod, peff::String &&varName, ExprNode *cond, StmtNode *body);
		XYLO_API ForEachStmtNode(const ForEachStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~ForEachStmtNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class WhileStmtNode : public StmtNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::RcObjectPtr<ExprNode> cond;
		peff::RcObjectPtr<StmtNode> body;

		XYLO_API WhileStmtNode(peff::Alloc *selfAllocator, Module *mod, ExprNode *cond, StmtNode *body);
		XYLO_API WhileStmtNode(const WhileStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~WhileStmtNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class ReturnStmtNode : public StmtNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::RcObjectPtr<ExprNode> value;

		XYLO_API ReturnStmtNode(peff::Alloc *selfAllocator, Module *mod, ExprNode *value);
		XYLO_API ReturnStmtNode(const ReturnStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~ReturnStmtNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class IfStmtNode : public StmtNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::RcObjectPtr<ExprNode> cond;
		peff::RcObjectPtr<StmtNode> trueBody, falseBody;

		XYLO_API IfStmtNode(peff::Alloc *selfAllocator, Module *mod, ExprNode *cond, StmtNode *trueBody, StmtNode *falseBody);
		XYLO_API IfStmtNode(const IfStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~IfStmtNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class CodeBlockStmtNode : public StmtNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::DynArray<peff::RcObjectPtr<StmtNode>> body;

		XYLO_API CodeBlockStmtNode(peff::Alloc *selfAllocator, Module *mod, peff::DynArray<peff::RcObjectPtr<StmtNode>> &&body);
		XYLO_API CodeBlockStmtNode(const CodeBlockStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~CodeBlockStmtNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class BadStmtNode : public StmtNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		XYLO_API BadStmtNode(peff::Alloc *selfAllocator, Module *mod);
		XYLO_API BadStmtNode(const BadStmtNode &rhs);
		XYLO_API ~BadStmtNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};
}

#endif
