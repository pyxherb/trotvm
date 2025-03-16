#include "expr.h"

using namespace xylo;

XYLO_API ExprNode::ExprNode(ExprKind exprKind, peff::Alloc *selfAllocator) : AstNode(AstNodeType::TypeName, selfAllocator), exprKind(exprKind) {
}

XYLO_API ExprNode::ExprNode(const ExprNode &rhs) : AstNode(rhs), exprKind(rhs.exprKind) {
}

XYLO_API ExprNode::~ExprNode() {
}

XYLO_API peff::RcObjectPtr<AstNode> UnaryExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;

	peff::RcObjectPtr<UnaryExprNode> duplicatedNode(peff::allocAndConstruct<UnaryExprNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API UnaryExprNode::UnaryExprNode(
	peff::Alloc *selfAllocator,
	UnaryOp unaryOp,
	ExprNode *operand)
	: ExprNode(ExprKind::Unary, selfAllocator),
	  unaryOp(unaryOp),
	  operand(operand) {
}

XYLO_API UnaryExprNode::UnaryExprNode(const UnaryExprNode &rhs, peff::Alloc *selfAllocator, bool &succeededOut) : ExprNode(rhs), unaryOp(rhs.unaryOp) {
	if (!(operand = rhs.operand->duplicate<ExprNode>(selfAllocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

XYLO_API UnaryExprNode::~UnaryExprNode() {
}

XYLO_API void UnaryExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<UnaryExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> BinaryExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<BinaryExprNode> duplicatedNode(peff::allocAndConstruct<BinaryExprNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API BinaryExprNode::BinaryExprNode(
	peff::Alloc *selfAllocator,
	BinaryOp binaryOp,
	ExprNode *lhs,
	ExprNode *rhs)
	: ExprNode(ExprKind::Binary, selfAllocator),
	  binaryOp(binaryOp),
	  lhs(lhs),
	  rhs(rhs) {
}

XYLO_API BinaryExprNode::BinaryExprNode(const BinaryExprNode &rhs, peff::Alloc *allocator, bool &succeededOut) : ExprNode(rhs), binaryOp(rhs.binaryOp) {
	if (!(this->lhs = rhs.lhs->duplicate<ExprNode>(allocator))) {
		succeededOut = false;
		return;
	}
	if (!(this->rhs = rhs.rhs->duplicate<ExprNode>(allocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

XYLO_API BinaryExprNode::~BinaryExprNode() {
}

XYLO_API void BinaryExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<BinaryExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> TernaryExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<TernaryExprNode> duplicatedNode(peff::allocAndConstruct<TernaryExprNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API TernaryExprNode::TernaryExprNode(
	peff::Alloc *selfAllocator,
	ExprNode *cond,
	ExprNode *lhs,
	ExprNode *rhs)
	: ExprNode(ExprKind::Ternary, selfAllocator),
	  cond(cond),
	  lhs(lhs),
	  rhs(rhs) {
}

XYLO_API TernaryExprNode::TernaryExprNode(const TernaryExprNode &rhs, peff::Alloc *allocator, bool &succeededOut) : ExprNode(rhs) {
	if (!(this->cond = rhs.cond->duplicate<ExprNode>(allocator))) {
		succeededOut = false;
		return;
	}
	if (!(this->lhs = rhs.lhs->duplicate<ExprNode>(allocator))) {
		succeededOut = false;
		return;
	}
	if (!(this->rhs = rhs.rhs->duplicate<ExprNode>(allocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

XYLO_API TernaryExprNode::~TernaryExprNode() {
}

XYLO_API void TernaryExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<TernaryExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> IdRefExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<IdRefExprNode> duplicatedNode(peff::allocAndConstruct<IdRefExprNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API IdRefExprNode::IdRefExprNode(
	peff::Alloc *selfAllocator,
	IdRefPtr &&idRefPtr)
	: ExprNode(ExprKind::IdRef, selfAllocator),
	  idRefPtr(std::move(idRefPtr)) {
}
XYLO_API IdRefExprNode::IdRefExprNode(const IdRefExprNode &rhs, peff::Alloc *allocator, bool &succeededOut) : ExprNode(rhs) {
	if (!(idRefPtr = duplicateIdRef(allocator, rhs.idRefPtr.get()))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}
XYLO_API IdRefExprNode::~IdRefExprNode() {
}

XYLO_API void IdRefExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<IdRefExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> I8LiteralExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<I8LiteralExprNode> duplicatedNode(peff::allocAndConstruct<I8LiteralExprNode>(newAllocator, sizeof(std::max_align_t), *this));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API I8LiteralExprNode::I8LiteralExprNode(
	peff::Alloc *selfAllocator,
	int8_t data)
	: ExprNode(ExprKind::I8, selfAllocator),
	  data(data) {
}
XYLO_API I8LiteralExprNode::I8LiteralExprNode(const I8LiteralExprNode &rhs) : ExprNode(rhs), data(rhs.data) {
}
XYLO_API I8LiteralExprNode::~I8LiteralExprNode() {
}

XYLO_API void I8LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<I8LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> I16LiteralExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<I16LiteralExprNode> duplicatedNode(peff::allocAndConstruct<I16LiteralExprNode>(newAllocator, sizeof(std::max_align_t), *this));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API I16LiteralExprNode::I16LiteralExprNode(
	peff::Alloc *selfAllocator,
	int16_t data)
	: ExprNode(ExprKind::I16, selfAllocator),
	  data(data) {
}
XYLO_API I16LiteralExprNode::I16LiteralExprNode(const I16LiteralExprNode &rhs) : ExprNode(rhs), data(rhs.data) {
}
XYLO_API I16LiteralExprNode::~I16LiteralExprNode() {
}

XYLO_API void I16LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<I16LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> I32LiteralExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<I32LiteralExprNode> duplicatedNode(peff::allocAndConstruct<I32LiteralExprNode>(newAllocator, sizeof(std::max_align_t), *this));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API I32LiteralExprNode::I32LiteralExprNode(
	peff::Alloc *selfAllocator,
	int32_t data)
	: ExprNode(ExprKind::I32, selfAllocator),
	  data(data) {
}
XYLO_API I32LiteralExprNode::I32LiteralExprNode(const I32LiteralExprNode &rhs) : ExprNode(rhs), data(rhs.data) {
}
XYLO_API I32LiteralExprNode::~I32LiteralExprNode() {
}

XYLO_API void I32LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<I32LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> I64LiteralExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<I64LiteralExprNode> duplicatedNode(peff::allocAndConstruct<I64LiteralExprNode>(newAllocator, sizeof(std::max_align_t), *this));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API I64LiteralExprNode::I64LiteralExprNode(
	peff::Alloc *selfAllocator,
	int64_t data)
	: ExprNode(ExprKind::I64, selfAllocator),
	  data(data) {
}
XYLO_API I64LiteralExprNode::I64LiteralExprNode(const I64LiteralExprNode &rhs) : ExprNode(rhs), data(rhs.data) {
}
XYLO_API I64LiteralExprNode::~I64LiteralExprNode() {
}

XYLO_API void I64LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<I64LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> U8LiteralExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<U8LiteralExprNode> duplicatedNode(peff::allocAndConstruct<U8LiteralExprNode>(newAllocator, sizeof(std::max_align_t), *this));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API U8LiteralExprNode::U8LiteralExprNode(
	peff::Alloc *selfAllocator,
	uint8_t data)
	: ExprNode(ExprKind::U8, selfAllocator),
	  data(data) {
}
XYLO_API U8LiteralExprNode::U8LiteralExprNode(const U8LiteralExprNode &rhs) : ExprNode(rhs), data(rhs.data) {
}
XYLO_API U8LiteralExprNode::~U8LiteralExprNode() {
}

XYLO_API void U8LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<U8LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> U16LiteralExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<U16LiteralExprNode> duplicatedNode(peff::allocAndConstruct<U16LiteralExprNode>(newAllocator, sizeof(std::max_align_t), *this));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API U16LiteralExprNode::U16LiteralExprNode(
	peff::Alloc *selfAllocator,
	uint16_t data)
	: ExprNode(ExprKind::U16, selfAllocator),
	  data(data) {
}
XYLO_API U16LiteralExprNode::U16LiteralExprNode(const U16LiteralExprNode &rhs) : ExprNode(rhs), data(rhs.data) {
}
XYLO_API U16LiteralExprNode::~U16LiteralExprNode() {
}

XYLO_API void U16LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<U16LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> U32LiteralExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<U32LiteralExprNode> duplicatedNode(peff::allocAndConstruct<U32LiteralExprNode>(newAllocator, sizeof(std::max_align_t), *this));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}
XYLO_API U32LiteralExprNode::U32LiteralExprNode(
	peff::Alloc *selfAllocator,
	uint32_t data)
	: ExprNode(ExprKind::U32, selfAllocator),
	  data(data) {
}
XYLO_API U32LiteralExprNode::U32LiteralExprNode(const U32LiteralExprNode &rhs) : ExprNode(rhs), data(rhs.data) {
}
XYLO_API U32LiteralExprNode::~U32LiteralExprNode() {
}

XYLO_API void U32LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<U32LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> U64LiteralExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<U64LiteralExprNode> duplicatedNode(peff::allocAndConstruct<U64LiteralExprNode>(newAllocator, sizeof(std::max_align_t), *this));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API U64LiteralExprNode::U64LiteralExprNode(
	peff::Alloc *selfAllocator,
	uint64_t data)
	: ExprNode(ExprKind::U64, selfAllocator),
	  data(data) {
}
XYLO_API U64LiteralExprNode::U64LiteralExprNode(const U64LiteralExprNode &rhs) : ExprNode(rhs), data(rhs.data) {
}
XYLO_API U64LiteralExprNode::~U64LiteralExprNode() {
}

XYLO_API void U64LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<U64LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> F32LiteralExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<F32LiteralExprNode> duplicatedNode(peff::allocAndConstruct<F32LiteralExprNode>(newAllocator, sizeof(std::max_align_t), *this));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API F32LiteralExprNode::F32LiteralExprNode(
	peff::Alloc *selfAllocator,
	float data)
	: ExprNode(ExprKind::F32, selfAllocator),
	  data(data) {
}
XYLO_API F32LiteralExprNode::F32LiteralExprNode(const F32LiteralExprNode &rhs) : ExprNode(rhs), data(rhs.data) {
}
XYLO_API F32LiteralExprNode::~F32LiteralExprNode() {
}

XYLO_API void F32LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<F32LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> F64LiteralExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<F64LiteralExprNode> duplicatedNode(peff::allocAndConstruct<F64LiteralExprNode>(newAllocator, sizeof(std::max_align_t), *this));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API F64LiteralExprNode::F64LiteralExprNode(
	peff::Alloc *selfAllocator,
	double data)
	: ExprNode(ExprKind::F64, selfAllocator),
	  data(data) {
}
XYLO_API F64LiteralExprNode::F64LiteralExprNode(const F64LiteralExprNode &rhs) : ExprNode(rhs), data(rhs.data) {
}
XYLO_API F64LiteralExprNode::~F64LiteralExprNode() {
}

XYLO_API void F64LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<F64LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> BoolLiteralExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<BoolLiteralExprNode> duplicatedNode(peff::allocAndConstruct<BoolLiteralExprNode>(newAllocator, sizeof(std::max_align_t), *this));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}
XYLO_API BoolLiteralExprNode::BoolLiteralExprNode(
	peff::Alloc *selfAllocator,
	bool data)
	: ExprNode(ExprKind::Bool, selfAllocator),
	  data(data) {
}
XYLO_API BoolLiteralExprNode::BoolLiteralExprNode(const BoolLiteralExprNode &rhs) : ExprNode(rhs), data(rhs.data) {
}
XYLO_API BoolLiteralExprNode::~BoolLiteralExprNode() {
}

XYLO_API void BoolLiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<BoolLiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> StringLiteralExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<StringLiteralExprNode> duplicatedNode(peff::allocAndConstruct<StringLiteralExprNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}
XYLO_API StringLiteralExprNode::StringLiteralExprNode(
	peff::Alloc *selfAllocator,
	peff::String &&data)
	: ExprNode(ExprKind::String, selfAllocator),
	  data(std::move(data)) {
}
XYLO_API StringLiteralExprNode::StringLiteralExprNode(const StringLiteralExprNode &rhs, peff::Alloc *allocator, bool &succeededOut) : ExprNode(rhs), data(allocator) {
	if (!peff::copy(data, rhs.data)) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}
XYLO_API StringLiteralExprNode::~StringLiteralExprNode() {
}

XYLO_API void StringLiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<StringLiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> NullptrLiteralExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<NullptrLiteralExprNode> duplicatedNode(peff::allocAndConstruct<NullptrLiteralExprNode>(newAllocator, sizeof(std::max_align_t), *this));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}
XYLO_API NullptrLiteralExprNode::NullptrLiteralExprNode(
	peff::Alloc *selfAllocator)
	: ExprNode(ExprKind::Nullptr, selfAllocator) {
}
XYLO_API NullptrLiteralExprNode::NullptrLiteralExprNode(const NullptrLiteralExprNode &rhs) : ExprNode(rhs) {
}
XYLO_API NullptrLiteralExprNode::~NullptrLiteralExprNode() {
}

XYLO_API void NullptrLiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<NullptrLiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> InitializerListExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<InitializerListExprNode> duplicatedNode(peff::allocAndConstruct<InitializerListExprNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}
XYLO_API InitializerListExprNode::InitializerListExprNode(
	peff::Alloc *selfAllocator)
	: ExprNode(ExprKind::InitializerList, selfAllocator),
	  elements(selfAllocator) {
}
XYLO_API InitializerListExprNode::InitializerListExprNode(const InitializerListExprNode &rhs, peff::Alloc *allocator, bool &succeededOut) : ExprNode(rhs), elements(allocator) {
	if (!elements.resize(rhs.elements.size())) {
		succeededOut = false;
		return;
	}

	for (size_t i = 0; i < elements.size(); ++i) {
		if (!(elements.at(i) = rhs.elements.at(i)->duplicate<ExprNode>(allocator))) {
			succeededOut = false;
			return;
		}
	}

	succeededOut = true;
}
XYLO_API InitializerListExprNode::~InitializerListExprNode() {
}

XYLO_API void InitializerListExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<InitializerListExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> DesignatedInitializerExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<DesignatedInitializerExprNode> duplicatedNode(peff::allocAndConstruct<DesignatedInitializerExprNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}
XYLO_API DesignatedInitializerExprNode::DesignatedInitializerExprNode(
	peff::Alloc *selfAllocator)
	: ExprNode(ExprKind::DesignatedInitializer, selfAllocator),
	  fields(selfAllocator) {
}
XYLO_API DesignatedInitializerExprNode::DesignatedInitializerExprNode(const DesignatedInitializerExprNode &rhs, peff::Alloc *allocator, bool &succeededOut) : ExprNode(rhs), fields(allocator) {
	for (auto i = rhs.fields.begin(); i != rhs.fields.end(); ++i) {
		peff::String copiedName(allocator);

		if (!copiedName.resize(i->first.size())) {
			succeededOut = false;
			return;
		}
		memcpy(copiedName.data(), i->first.data(), i->first.size());

		peff::RcObjectPtr<ExprNode> duplicatedValue;

		if (!(duplicatedValue = i->second->duplicate<ExprNode>(allocator))) {
			succeededOut = false;
			return;
		}

		if(!fields.pushBack({ std::move(copiedName), std::move(duplicatedValue) })) {
			succeededOut = false;
			return;
		}
	}

	succeededOut = true;
}
XYLO_API DesignatedInitializerExprNode::~DesignatedInitializerExprNode() {
}

XYLO_API void DesignatedInitializerExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<DesignatedInitializerExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> CallExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<CallExprNode> duplicatedNode(peff::allocAndConstruct<CallExprNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}
XYLO_API CallExprNode::CallExprNode(
	peff::Alloc *selfAllocator,
	ExprNode *target,
	peff::DynArray<peff::RcObjectPtr<ExprNode>> &&args)
	: ExprNode(ExprKind::Call, selfAllocator),
	  target(target),
	  args(std::move(args)) {
}
XYLO_API CallExprNode::CallExprNode(const CallExprNode &rhs, peff::Alloc *allocator, bool &succeededOut)
	: ExprNode(rhs), args(allocator) {
	if (!(target = rhs.target->duplicate<ExprNode>(allocator))) {
		succeededOut = false;
		return;
	}

	if (!args.resize(rhs.args.size())) {
		succeededOut = false;
		return;
	}

	for (size_t i = 0; i < args.size(); ++i) {
		if (!(args.at(i) = rhs.args.at(i)->duplicate<ExprNode>(allocator))) {
			succeededOut = false;
			return;
		}
	}
}
XYLO_API CallExprNode::~CallExprNode() {
}

XYLO_API void CallExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<CallExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> MacroCallExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<MacroCallExprNode> duplicatedNode(peff::allocAndConstruct<MacroCallExprNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}
XYLO_API MacroCallExprNode::MacroCallExprNode(
	peff::Alloc *selfAllocator,
	IdRefPtr &&target,
	peff::DynArray<peff::RcObjectPtr<ExprNode>> &&args)
	: ExprNode(ExprKind::MacroCall, selfAllocator),
	  target(std::move(target)),
	  args(std::move(args)) {
}
XYLO_API MacroCallExprNode::MacroCallExprNode(const MacroCallExprNode &rhs, peff::Alloc *allocator, bool &succeededOut)
	: ExprNode(rhs), args(allocator) {
	if (!(target = duplicateIdRef(allocator, rhs.target.get()))) {
		succeededOut = false;
		return;
	}

	if (!args.resize(rhs.args.size())) {
		succeededOut = false;
		return;
	}

	for (size_t i = 0; i < args.size(); ++i) {
		if (!(args.at(i) = rhs.args.at(i)->duplicate<ExprNode>(allocator))) {
			succeededOut = false;
			return;
		}
	}
}
XYLO_API MacroCallExprNode::~MacroCallExprNode() {
}

XYLO_API void MacroCallExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<MacroCallExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> CastExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<CastExprNode> duplicatedNode(peff::allocAndConstruct<CastExprNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}
XYLO_API CastExprNode::CastExprNode(
	peff::Alloc *selfAllocator, TypeNameNode *targetType, ExprNode *source)
	: ExprNode(ExprKind::Cast, selfAllocator),
	  source(source) {
}
XYLO_API CastExprNode::CastExprNode(const CastExprNode &rhs, peff::Alloc *allocator, bool &succeededOut)
	: ExprNode(rhs) {
	if (!(targetType = rhs.targetType->duplicate<TypeNameNode>(allocator))) {
		succeededOut = false;
		return;
	}

	if (!(source = rhs.source->duplicate<ExprNode>(allocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}
XYLO_API CastExprNode::~CastExprNode() {
}

XYLO_API void CastExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<CastExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> WrapperExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<WrapperExprNode> duplicatedNode(peff::allocAndConstruct<WrapperExprNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}
XYLO_API WrapperExprNode::WrapperExprNode(
	peff::Alloc *selfAllocator, ExprNode *target)
	: ExprNode(ExprKind::Wrapper, selfAllocator),
	  target(target) {
}
XYLO_API WrapperExprNode::WrapperExprNode(const WrapperExprNode &rhs, peff::Alloc *allocator, bool &succeededOut)
	: ExprNode(rhs) {
	if (!(target = rhs.target->duplicate<ExprNode>(allocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}
XYLO_API WrapperExprNode::~WrapperExprNode() {
}

XYLO_API void WrapperExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<WrapperExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> VolatileExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<VolatileExprNode> duplicatedNode(peff::allocAndConstruct<VolatileExprNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}
XYLO_API VolatileExprNode::VolatileExprNode(
	peff::Alloc *selfAllocator, ExprNode *target)
	: ExprNode(ExprKind::Volatile, selfAllocator),
	  target(target) {
}
XYLO_API VolatileExprNode::VolatileExprNode(const VolatileExprNode &rhs, peff::Alloc *allocator, bool &succeededOut)
	: ExprNode(rhs) {
	if (!(target = rhs.target->duplicate<ExprNode>(allocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}
XYLO_API VolatileExprNode::~VolatileExprNode() {
}

XYLO_API void VolatileExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<VolatileExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> TypeNameExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<TypeNameExprNode> duplicatedNode(peff::allocAndConstruct<TypeNameExprNode>(newAllocator, sizeof(std::max_align_t), *this, newAllocator, succeeded));
	if((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}
XYLO_API TypeNameExprNode::TypeNameExprNode(
	peff::Alloc *selfAllocator, TypeNameNode *type)
	: ExprNode(ExprKind::TypeName, selfAllocator),
	  type(type) {
}
XYLO_API TypeNameExprNode::TypeNameExprNode(const TypeNameExprNode &rhs, peff::Alloc *allocator, bool &succeededOut)
	: ExprNode(rhs) {
	if (!(type = rhs.type->duplicate<TypeNameNode>(allocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}
XYLO_API TypeNameExprNode::~TypeNameExprNode() {
}

XYLO_API void TypeNameExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<TypeNameExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API peff::RcObjectPtr<AstNode> BadExprNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<BadExprNode> duplicatedNode(peff::allocAndConstruct<BadExprNode>(newAllocator, sizeof(std::max_align_t), *this));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}
XYLO_API BadExprNode::BadExprNode(
	peff::Alloc *selfAllocator)
	: ExprNode(ExprKind::TypeName, selfAllocator) {
}
XYLO_API BadExprNode::BadExprNode(const BadExprNode &rhs)
	: ExprNode(rhs) {
}
XYLO_API BadExprNode::~BadExprNode() {
}

XYLO_API void BadExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<BadExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}
