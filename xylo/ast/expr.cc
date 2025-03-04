#include "expr.h"

using namespace xylo;

XYLO_API ExprNode::ExprNode(ExprKind exprKind, peff::Alloc *selfAllocator) : AstNode(AstNodeType::TypeName, selfAllocator), exprKind(exprKind) {
}

XYLO_API ExprNode::ExprNode(const ExprNode &rhs) : AstNode(rhs), exprKind(rhs.exprKind) {
}

XYLO_API ExprNode::~ExprNode() {
}

XYLO_API UnaryExprNode::UnaryExprNode(
	peff::Alloc *selfAllocator,
	UnaryOp unaryOp,
	ExprNode *operand)
	: ExprNode(ExprKind::Unary, selfAllocator),
	  unaryOp(unaryOp),
	  operand(operand) {
}

XYLO_API UnaryExprNode::~UnaryExprNode() {
}

XYLO_API void UnaryExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<UnaryExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
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

XYLO_API BinaryExprNode::~BinaryExprNode() {
}

XYLO_API void BinaryExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<BinaryExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
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

XYLO_API TernaryExprNode::~TernaryExprNode() {
}

XYLO_API void TernaryExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<TernaryExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API IdRefExprNode::IdRefExprNode(
	peff::Alloc *selfAllocator,
	IdRefPtr &&idRefPtr)
	: ExprNode(ExprKind::IdRef, selfAllocator),
	  idRefPtr(std::move(idRefPtr)) {
}
XYLO_API IdRefExprNode::~IdRefExprNode() {
}

XYLO_API void IdRefExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<IdRefExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API I8LiteralExprNode::I8LiteralExprNode(
	peff::Alloc *selfAllocator,
	int8_t data)
	: ExprNode(ExprKind::I8, selfAllocator),
	  data(data) {
}
XYLO_API I8LiteralExprNode::~I8LiteralExprNode() {
}

XYLO_API void I8LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<I8LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API I16LiteralExprNode::I16LiteralExprNode(
	peff::Alloc *selfAllocator,
	int16_t data)
	: ExprNode(ExprKind::I16, selfAllocator),
	  data(data) {
}
XYLO_API I16LiteralExprNode::~I16LiteralExprNode() {
}

XYLO_API void I16LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<I16LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API I32LiteralExprNode::I32LiteralExprNode(
	peff::Alloc *selfAllocator,
	int32_t data)
	: ExprNode(ExprKind::I32, selfAllocator),
	  data(data) {
}
XYLO_API I32LiteralExprNode::~I32LiteralExprNode() {
}

XYLO_API void I32LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<I32LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API I64LiteralExprNode::I64LiteralExprNode(
	peff::Alloc *selfAllocator,
	int64_t data)
	: ExprNode(ExprKind::I64, selfAllocator),
	  data(data) {
}
XYLO_API I64LiteralExprNode::~I64LiteralExprNode() {
}

XYLO_API void I64LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<I64LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API U8LiteralExprNode::U8LiteralExprNode(
	peff::Alloc *selfAllocator,
	uint8_t data)
	: ExprNode(ExprKind::U8, selfAllocator),
	  data(data) {
}
XYLO_API U8LiteralExprNode::~U8LiteralExprNode() {
}

XYLO_API void U8LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<U8LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API U16LiteralExprNode::U16LiteralExprNode(
	peff::Alloc *selfAllocator,
	uint16_t data)
	: ExprNode(ExprKind::U16, selfAllocator),
	  data(data) {
}
XYLO_API U16LiteralExprNode::~U16LiteralExprNode() {
}

XYLO_API void U16LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<U16LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API U32LiteralExprNode::U32LiteralExprNode(
	peff::Alloc *selfAllocator,
	uint32_t data)
	: ExprNode(ExprKind::U32, selfAllocator),
	  data(data) {
}
XYLO_API U32LiteralExprNode::~U32LiteralExprNode() {
}

XYLO_API void U32LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<U32LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API U64LiteralExprNode::U64LiteralExprNode(
	peff::Alloc *selfAllocator,
	uint64_t data)
	: ExprNode(ExprKind::U64, selfAllocator),
	  data(data) {
}
XYLO_API U64LiteralExprNode::~U64LiteralExprNode() {
}

XYLO_API void U64LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<U64LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API F32LiteralExprNode::F32LiteralExprNode(
	peff::Alloc *selfAllocator,
	float data)
	: ExprNode(ExprKind::F32, selfAllocator),
	  data(data) {
}
XYLO_API F32LiteralExprNode::~F32LiteralExprNode() {
}

XYLO_API void F32LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<F32LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API F64LiteralExprNode::F64LiteralExprNode(
	peff::Alloc *selfAllocator,
	double data)
	: ExprNode(ExprKind::F64, selfAllocator),
	  data(data) {
}
XYLO_API F64LiteralExprNode::~F64LiteralExprNode() {
}

XYLO_API void F64LiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<F64LiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API BoolLiteralExprNode::BoolLiteralExprNode(
	peff::Alloc *selfAllocator,
	bool data)
	: ExprNode(ExprKind::Bool, selfAllocator),
	  data(data) {
}
XYLO_API BoolLiteralExprNode::~BoolLiteralExprNode() {
}

XYLO_API void BoolLiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<BoolLiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API StringLiteralExprNode::StringLiteralExprNode(
	peff::Alloc *selfAllocator,
	peff::String &&data)
	: ExprNode(ExprKind::String, selfAllocator),
	  data(std::move(data)) {
}
XYLO_API StringLiteralExprNode::~StringLiteralExprNode() {
}

XYLO_API void StringLiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<StringLiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API NullptrLiteralExprNode::NullptrLiteralExprNode(
	peff::Alloc *selfAllocator)
	: ExprNode(ExprKind::Nullptr, selfAllocator) {
}
XYLO_API NullptrLiteralExprNode::~NullptrLiteralExprNode() {
}

XYLO_API void NullptrLiteralExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<NullptrLiteralExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API InitializerListExprNode::InitializerListExprNode(
	peff::Alloc *selfAllocator,
	peff::DynArray<peff::RcObjectPtr<ExprNode>> &&elements)
	:ExprNode(ExprKind::InitializerList, selfAllocator),
	elements(std::move(elements)) {
}
XYLO_API InitializerListExprNode::~InitializerListExprNode() {

}

XYLO_API void InitializerListExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<InitializerListExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API CallExprNode::CallExprNode(
	peff::Alloc *selfAllocator,
	ExprNode *target,
	peff::DynArray<peff::RcObjectPtr<ExprNode>> &&args)
	:ExprNode(ExprKind::Call, selfAllocator),
	target(target),
	args(std::move(args)) {
}
XYLO_API CallExprNode::~CallExprNode() {

}

XYLO_API void CallExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<CallExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API MacroCallExprNode::MacroCallExprNode(
	peff::Alloc *selfAllocator,
	IdRefPtr &&target,
	peff::DynArray<peff::RcObjectPtr<ExprNode>> &&args)
	:ExprNode(ExprKind::MacroCall, selfAllocator),
	target(std::move(target)),
	args(std::move(args)) {
}
XYLO_API MacroCallExprNode::~MacroCallExprNode() {

}

XYLO_API void MacroCallExprNode::onRefZero() noexcept {
	peff::destroyAndRelease<MacroCallExprNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}
