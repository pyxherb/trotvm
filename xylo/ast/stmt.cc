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
	if (!copiedName.build(varDefEntry->name)) {
		return {};
	}

	peff::RcObjectPtr<TypeNameNode> type = varDefEntry->type->duplicate<TypeNameNode>(allocator);
	if (!type) {
		return {};
	}

	peff::RcObjectPtr<ExprNode> initialValue = varDefEntry->initialValue->duplicate<ExprNode>(allocator);
	if (!initialValue) {
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

XYLO_API VarDefStmtNode::VarDefStmtNode(peff::Alloc *selfAllocator, peff::DynArray<VarDefEntryPtr> &&varDefEntries) : StmtNode(StmtKind::VarDef, selfAllocator), varDefEntries(std::move(varDefEntries)) {
}

XYLO_API VarDefStmtNode::VarDefStmtNode(const VarDefStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut) : StmtNode(rhs), varDefEntries(allocator) {
	if (!(varDefEntries.resize(rhs.varDefEntries.size()))) {
		succeededOut = false;
		return;
	}

	for (size_t i = 0; i < varDefEntries.size(); ++i) {
		if (!(varDefEntries.at(i) = duplicateVarDefEntry(rhs.varDefEntries.at(i).get(), allocator))) {
			succeededOut = false;
			return;
		}
	}

	succeededOut = true;
}

XYLO_API VarDefStmtNode::~VarDefStmtNode() {
}

XYLO_API peff::RcObjectPtr<AstNode> BreakStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<ExprStmtNode> duplicatedNode(peff::allocAndConstruct<ExprStmtNode>(newAllocator, sizeof(std::max_align_t), *this));
	if (!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API BreakStmtNode::BreakStmtNode(peff::Alloc *selfAllocator) : StmtNode(StmtKind::VarDef, selfAllocator) {
}

XYLO_API BreakStmtNode::BreakStmtNode(const BreakStmtNode &rhs) : StmtNode(rhs) {
}

XYLO_API BreakStmtNode::~BreakStmtNode() {
}

XYLO_API peff::RcObjectPtr<AstNode> ContinueStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<ExprStmtNode> duplicatedNode(peff::allocAndConstruct<ExprStmtNode>(newAllocator, sizeof(std::max_align_t), *this));
	if (!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API ContinueStmtNode::ContinueStmtNode(peff::Alloc *selfAllocator) : StmtNode(StmtKind::VarDef, selfAllocator) {
}

XYLO_API ContinueStmtNode::ContinueStmtNode(const ContinueStmtNode &rhs) : StmtNode(rhs) {
}

XYLO_API ContinueStmtNode::~ContinueStmtNode() {
}

XYLO_API peff::RcObjectPtr<AstNode> ForStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<ExprStmtNode> duplicatedNode(peff::allocAndConstruct<ExprStmtNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API ForStmtNode::ForStmtNode(peff::Alloc *selfAllocator, peff::DynArray<VarDefEntryPtr> &&varDefEntries, ExprNode *cond, ExprNode *step, StmtNode *body) : StmtNode(StmtKind::For, selfAllocator), varDefEntries(std::move(varDefEntries)), cond(cond), step(step), body(body) {
}

XYLO_API ForStmtNode::ForStmtNode(const ForStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut) : StmtNode(rhs), varDefEntries(allocator) {
	if (!(varDefEntries.resize(rhs.varDefEntries.size()))) {
		succeededOut = false;
		return;
	}

	for (size_t i = 0; i < varDefEntries.size(); ++i) {
		if (!(varDefEntries.at(i) = duplicateVarDefEntry(rhs.varDefEntries.at(i).get(), allocator))) {
			succeededOut = false;
			return;
		}
	}

	if (!(cond = rhs.cond->duplicate<ExprNode>(allocator))) {
		succeededOut = false;
		return;
	}

	if (!(step = rhs.step->duplicate<ExprNode>(allocator))) {
		succeededOut = false;
		return;
	}

	if (!(body = rhs.body->duplicate<StmtNode>(allocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

XYLO_API ForStmtNode::~ForStmtNode() {
}

XYLO_API peff::RcObjectPtr<AstNode> ForEachStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<ExprStmtNode> duplicatedNode(peff::allocAndConstruct<ExprStmtNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API ForEachStmtNode::ForEachStmtNode(peff::Alloc *selfAllocator, peff::String &&varName, ExprNode *cond, StmtNode *body) : StmtNode(StmtKind::ForEach, selfAllocator), varName(std::move(varName)), cond(cond), body(body) {
}

XYLO_API ForEachStmtNode::ForEachStmtNode(const ForEachStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut) : StmtNode(rhs), varName(allocator) {
	if (!varName.build(rhs.varName)) {
		succeededOut = false;
		return;
	}

	if (!(cond = rhs.cond->duplicate<ExprNode>(allocator))) {
		succeededOut = false;
		return;
	}

	if (!(body = rhs.body->duplicate<StmtNode>(allocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

XYLO_API ForEachStmtNode::~ForEachStmtNode() {
}

XYLO_API peff::RcObjectPtr<AstNode> WhileStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<ExprStmtNode> duplicatedNode(peff::allocAndConstruct<ExprStmtNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API WhileStmtNode::WhileStmtNode(peff::Alloc *selfAllocator, ExprNode *cond, StmtNode *body) : StmtNode(StmtKind::While, selfAllocator), cond(cond), body(body) {
}

XYLO_API WhileStmtNode::WhileStmtNode(const WhileStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut) : StmtNode(rhs) {
	if (!(cond = rhs.cond->duplicate<ExprNode>(allocator))) {
		succeededOut = false;
		return;
	}

	if (!(body = rhs.body->duplicate<StmtNode>(allocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

XYLO_API WhileStmtNode::~WhileStmtNode() {
}

XYLO_API peff::RcObjectPtr<AstNode> ReturnStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<ExprStmtNode> duplicatedNode(peff::allocAndConstruct<ExprStmtNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API ReturnStmtNode::ReturnStmtNode(peff::Alloc *selfAllocator, ExprNode *value) : StmtNode(StmtKind::Return, selfAllocator), value(value) {
}

XYLO_API ReturnStmtNode::ReturnStmtNode(const ReturnStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut) : StmtNode(rhs) {
	if (!(value = rhs.value->duplicate<ExprNode>(allocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

XYLO_API ReturnStmtNode::~ReturnStmtNode() {
}

XYLO_API peff::RcObjectPtr<AstNode> IfStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<ExprStmtNode> duplicatedNode(peff::allocAndConstruct<ExprStmtNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API IfStmtNode::IfStmtNode(peff::Alloc *selfAllocator, ExprNode *cond, StmtNode *trueBody, StmtNode *falseBody) : StmtNode(StmtKind::If, selfAllocator), cond(cond), trueBody(trueBody), falseBody(falseBody) {
}

XYLO_API IfStmtNode::IfStmtNode(const IfStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut) : StmtNode(rhs) {
	if (!(cond = rhs.cond->duplicate<ExprNode>(allocator))) {
		succeededOut = false;
		return;
	}

	if (!(trueBody = rhs.trueBody->duplicate<StmtNode>(allocator))) {
		succeededOut = false;
		return;
	}

	if (!(falseBody = rhs.falseBody->duplicate<StmtNode>(allocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

XYLO_API IfStmtNode::~IfStmtNode() {
}

XYLO_API peff::RcObjectPtr<AstNode> CodeBlockStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<CodeBlockStmtNode> duplicatedNode(peff::allocAndConstruct<CodeBlockStmtNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API CodeBlockStmtNode::CodeBlockStmtNode(peff::Alloc *selfAllocator, peff::DynArray<peff::RcObjectPtr<StmtNode>> &&body): StmtNode(StmtKind::CodeBlock, selfAllocator), body(std::move(body)) {
}

XYLO_API CodeBlockStmtNode::CodeBlockStmtNode(const CodeBlockStmtNode &rhs, peff::Alloc *allocator, bool &succeededOut): StmtNode(rhs), body(allocator) {
	if(!(body.resize(rhs.body.size()))) {
		succeededOut = false;
		return;
	}

	for(size_t i = 0 ; i < body.size(); ++i) {
		if(!(body.at(i) = rhs.body.at(i)->duplicate<StmtNode>(allocator))) {
			succeededOut = false;
			return;
		}
	}

	succeededOut = true;
}

XYLO_API CodeBlockStmtNode::~CodeBlockStmtNode() {
}

XYLO_API peff::RcObjectPtr<AstNode> BadStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<BadStmtNode> duplicatedNode(peff::allocAndConstruct<BadStmtNode>(newAllocator, sizeof(std::max_align_t), *this));
	if (!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API BadStmtNode::BadStmtNode(peff::Alloc *selfAllocator): StmtNode(StmtKind::Bad, selfAllocator) {
}

XYLO_API BadStmtNode::BadStmtNode(const BadStmtNode &rhs): StmtNode(rhs) {
}

XYLO_API BadStmtNode::~BadStmtNode() {
}
