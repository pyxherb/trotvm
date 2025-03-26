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

XYLO_API ExprStmtNode::ExprStmtNode(peff::Alloc *selfAllocator, Module *mod, ExprNode *expr) : StmtNode(StmtKind::Expr, selfAllocator, mod), expr(expr) {
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

XYLO_API void ExprStmtNode::onRefZero() noexcept {
	peff::destroyAndRelease(selfAllocator.get(), this, sizeof(std::max_align_t));
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
	peff::RcObjectPtr<VarDefStmtNode> duplicatedNode(peff::allocAndConstruct<VarDefStmtNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API VarDefStmtNode::VarDefStmtNode(peff::Alloc *selfAllocator, Module *mod, peff::DynArray<VarDefEntryPtr> &&varDefEntries) : StmtNode(StmtKind::VarDef, selfAllocator, mod), varDefEntries(std::move(varDefEntries)) {
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

XYLO_API void VarDefStmtNode::onRefZero() noexcept {
	peff::destroyAndRelease(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> BreakStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<BreakStmtNode> duplicatedNode(peff::allocAndConstruct<BreakStmtNode>(newAllocator, sizeof(std::max_align_t), *this));
	if (!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API BreakStmtNode::BreakStmtNode(peff::Alloc *selfAllocator, Module *mod) : StmtNode(StmtKind::VarDef, selfAllocator, mod) {
}

XYLO_API BreakStmtNode::BreakStmtNode(const BreakStmtNode &rhs) : StmtNode(rhs) {
}

XYLO_API BreakStmtNode::~BreakStmtNode() {
}

XYLO_API void BreakStmtNode::onRefZero() noexcept {
	peff::destroyAndRelease(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> ContinueStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<ContinueStmtNode> duplicatedNode(peff::allocAndConstruct<ContinueStmtNode>(newAllocator, sizeof(std::max_align_t), *this));
	if (!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API ContinueStmtNode::ContinueStmtNode(peff::Alloc *selfAllocator, Module *mod) : StmtNode(StmtKind::VarDef, selfAllocator, mod) {
}

XYLO_API ContinueStmtNode::ContinueStmtNode(const ContinueStmtNode &rhs) : StmtNode(rhs) {
}

XYLO_API ContinueStmtNode::~ContinueStmtNode() {
}

XYLO_API void ContinueStmtNode::onRefZero() noexcept {
	peff::destroyAndRelease(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> ForStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<ForStmtNode> duplicatedNode(peff::allocAndConstruct<ForStmtNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API ForStmtNode::ForStmtNode(peff::Alloc *selfAllocator, Module *mod, peff::DynArray<VarDefEntryPtr> &&varDefEntries, ExprNode *cond, ExprNode *step, StmtNode *body) : StmtNode(StmtKind::For, selfAllocator, mod), varDefEntries(std::move(varDefEntries)), cond(cond), step(step), body(body) {
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

XYLO_API void ForStmtNode::onRefZero() noexcept {
	peff::destroyAndRelease(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> ForEachStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<ForEachStmtNode> duplicatedNode(peff::allocAndConstruct<ForEachStmtNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API ForEachStmtNode::ForEachStmtNode(peff::Alloc *selfAllocator, Module *mod, peff::String &&varName, ExprNode *cond, StmtNode *body) : StmtNode(StmtKind::ForEach, selfAllocator, mod), varName(std::move(varName)), cond(cond), body(body) {
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

XYLO_API void ForEachStmtNode::onRefZero() noexcept {
	peff::destroyAndRelease(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> WhileStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<WhileStmtNode> duplicatedNode(peff::allocAndConstruct<WhileStmtNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API WhileStmtNode::WhileStmtNode(peff::Alloc *selfAllocator, Module *mod, ExprNode *cond, StmtNode *body) : StmtNode(StmtKind::While, selfAllocator, mod), cond(cond), body(body) {
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

XYLO_API void WhileStmtNode::onRefZero() noexcept {
	peff::destroyAndRelease(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> ReturnStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<ReturnStmtNode> duplicatedNode(peff::allocAndConstruct<ReturnStmtNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API ReturnStmtNode::ReturnStmtNode(peff::Alloc *selfAllocator, Module *mod, ExprNode *value) : StmtNode(StmtKind::Return, selfAllocator, mod), value(value) {
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

XYLO_API void ReturnStmtNode::onRefZero() noexcept {
	peff::destroyAndRelease(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> IfStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<IfStmtNode> duplicatedNode(peff::allocAndConstruct<IfStmtNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API IfStmtNode::IfStmtNode(peff::Alloc *selfAllocator, Module *mod, ExprNode *cond, StmtNode *trueBody, StmtNode *falseBody) : StmtNode(StmtKind::If, selfAllocator, mod), cond(cond), trueBody(trueBody), falseBody(falseBody) {
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

XYLO_API void IfStmtNode::onRefZero() noexcept {
	peff::destroyAndRelease(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> CodeBlockStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<CodeBlockStmtNode> duplicatedNode(peff::allocAndConstruct<CodeBlockStmtNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API CodeBlockStmtNode::CodeBlockStmtNode(peff::Alloc *selfAllocator, Module *mod, peff::DynArray<peff::RcObjectPtr<StmtNode>> &&body): StmtNode(StmtKind::CodeBlock, selfAllocator, mod), body(std::move(body)) {
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

XYLO_API void CodeBlockStmtNode::onRefZero() noexcept {
	peff::destroyAndRelease(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> BadStmtNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<BadStmtNode> duplicatedNode(peff::allocAndConstruct<BadStmtNode>(newAllocator, sizeof(std::max_align_t), *this));
	if (!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API BadStmtNode::BadStmtNode(peff::Alloc *selfAllocator, Module *mod): StmtNode(StmtKind::Bad, selfAllocator, mod) {
}

XYLO_API BadStmtNode::BadStmtNode(const BadStmtNode &rhs): StmtNode(rhs) {
}

XYLO_API BadStmtNode::~BadStmtNode() {
}

XYLO_API void BadStmtNode::onRefZero() noexcept {
	peff::destroyAndRelease(selfAllocator.get(), this, sizeof(std::max_align_t));
}
