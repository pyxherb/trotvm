#include "stmt.h"

using namespace xylo;

XYLO_API peff::RcObjectPtr<AstNode> ExprStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<ExprStmtNode> duplicatedNode(peff::allocAndConstruct<ExprStmtNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API ExprStmtNode::ExprStmtNode(peff::Alloc *selfAllocator, ExprNode *expr) : StmtNode(StmtKind::Expr, selfAllocator), expr(expr) {
}

XYLO_API ExprStmtNode::ExprStmtNode(const ExprStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut) : StmtNode(rhs) {
	if (!(expr = rhs.expr->duplicate<ExprNode>(allocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

XYLO_API ExprStmtNode::~ExprStmtNode() {
}

XYLO_API VarDefEntry::VarDefEntry(peff::Alloc *selfAllocator, peff::String &&name, TypeNameNode *type, ExprNode *initialValue) : selfAllocator(selfAllocator), name(std::move(name)), type(type), initialValue(initialValue) {
}
XYLO_API VarDefEntry::~VarDefEntry() {
}
XYLO_API void VarDefEntry::dealloc() noexcept {
	peff::destroyAndRelease<VarDefEntry>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API VarDefEntryPtr xylo::duplicateVarDefEntry(VarDefEntry *varDefEntry, peff::Alloc *allocator) {
	peff::String copiedName(allocator);
	if(!copiedName.build(varDefEntry->name)) {
		return {};
	}

	peff::RcObjectPtr<TypeNameNode> type = varDefEntry->type->duplicate<TypeNameNode>(allocator);
	if(!type) {
		return {};
	}

	peff::RcObjectPtr<ExprNode> initialValue = varDefEntry->initialValue->duplicate<ExprNode>(allocator);
	if(!initialValue) {
		return {};
	}

	return VarDefEntryPtr(peff::allocAndConstruct<VarDefEntry>(allocator, sizeof(std::max_align_t), allocator, std::move(copiedName), type.get(), initialValue.get()));
}

XYLO_API peff::RcObjectPtr<AstNode> VarDefStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<ExprStmtNode> duplicatedNode(peff::allocAndConstruct<ExprStmtNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API VarDefStmtNode::VarDefStmtNode(peff::Alloc *selfAllocator, peff::DynArray<VarDefEntry> &&varDefEntries) : StmtNode(StmtKind::VarDef, selfAllocator), varDefEntries(std::move(varDefEntries)) {
}

XYLO_API VarDefStmtNode::VarDefStmtNode(const VarDefStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut) : StmtNode(rhs), varDefEntries(allocator) {
	if(!(varDefEntries.resize(rhs.varDefEntries.size()))) {
		succeededOut = false;
		return;
	}

	for(size_t i = 0 ; i < varDefEntries.size(); ++i) {
		if(!(varDefEntries.at(i) = duplicateVarDefEntry(rhs.varDefEntries.at(i).get(), allocator))) {
			succeededOut = false;
			return;
		}
	}

	succeededOut = true;
}

XYLO_API VarDefStmtNode::~VarDefStmtNode() {
}
