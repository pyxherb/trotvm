#include "typename.h"

using namespace xylo;

XYLO_API peff::RcObjectPtr<AstNode> VoidTypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<VoidTypeNameNode> duplicatedNode(peff::allocAndConstruct<VoidTypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API VoidTypeNameNode::VoidTypeNameNode(peff::Alloc *selfAllocator, Module *mod) : TypeNameNode(TypeNameKind::Void, selfAllocator, mod) {
}

XYLO_API VoidTypeNameNode::VoidTypeNameNode(const VoidTypeNameNode &rhs, peff::Alloc *selfAllocator) : TypeNameNode(rhs, selfAllocator) {
}

XYLO_API VoidTypeNameNode::~VoidTypeNameNode() {
}

XYLO_API void VoidTypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<VoidTypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> I8TypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<I8TypeNameNode> duplicatedNode(peff::allocAndConstruct<I8TypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API I8TypeNameNode::I8TypeNameNode(peff::Alloc *selfAllocator, Module *mod) : TypeNameNode(TypeNameKind::I8, selfAllocator, mod) {
}

XYLO_API I8TypeNameNode::I8TypeNameNode(const I8TypeNameNode &rhs, peff::Alloc *selfAllocator) : TypeNameNode(rhs, selfAllocator) {
}

XYLO_API I8TypeNameNode::~I8TypeNameNode() {
}

XYLO_API void I8TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<I8TypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> I16TypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<I16TypeNameNode> duplicatedNode(peff::allocAndConstruct<I16TypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API I16TypeNameNode::I16TypeNameNode(peff::Alloc *selfAllocator, Module *mod) : TypeNameNode(TypeNameKind::I16, selfAllocator, mod) {
}

XYLO_API I16TypeNameNode::I16TypeNameNode(const I16TypeNameNode &rhs, peff::Alloc *selfAllocator) : TypeNameNode(rhs, selfAllocator) {
}

XYLO_API I16TypeNameNode::~I16TypeNameNode() {
}

XYLO_API void I16TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<I16TypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> I32TypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<I32TypeNameNode> duplicatedNode(peff::allocAndConstruct<I32TypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API I32TypeNameNode::I32TypeNameNode(peff::Alloc *selfAllocator, Module *mod) : TypeNameNode(TypeNameKind::I32, selfAllocator, mod) {
}

XYLO_API I32TypeNameNode::I32TypeNameNode(const I32TypeNameNode &rhs, peff::Alloc *selfAllocator) : TypeNameNode(rhs, selfAllocator) {
}

XYLO_API I32TypeNameNode::~I32TypeNameNode() {
}

XYLO_API void I32TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<I32TypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> I64TypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<I64TypeNameNode> duplicatedNode(peff::allocAndConstruct<I64TypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API I64TypeNameNode::I64TypeNameNode(peff::Alloc *selfAllocator, Module *mod) : TypeNameNode(TypeNameKind::I64, selfAllocator, mod) {
}

XYLO_API I64TypeNameNode::I64TypeNameNode(const I64TypeNameNode &rhs, peff::Alloc *selfAllocator) : TypeNameNode(rhs, selfAllocator) {
}

XYLO_API I64TypeNameNode::~I64TypeNameNode() {
}

XYLO_API void I64TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<I64TypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> U8TypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<U8TypeNameNode> duplicatedNode(peff::allocAndConstruct<U8TypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API U8TypeNameNode::U8TypeNameNode(peff::Alloc *selfAllocator, Module *mod) : TypeNameNode(TypeNameKind::U8, selfAllocator, mod) {
}

XYLO_API U8TypeNameNode::U8TypeNameNode(const U8TypeNameNode &rhs, peff::Alloc *selfAllocator) : TypeNameNode(rhs, selfAllocator) {
}

XYLO_API U8TypeNameNode::~U8TypeNameNode() {
}

XYLO_API void U8TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<U8TypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> U16TypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<U16TypeNameNode> duplicatedNode(peff::allocAndConstruct<U16TypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API U16TypeNameNode::U16TypeNameNode(peff::Alloc *selfAllocator, Module *mod) : TypeNameNode(TypeNameKind::U16, selfAllocator, mod) {
}

XYLO_API U16TypeNameNode::U16TypeNameNode(const U16TypeNameNode &rhs, peff::Alloc *selfAllocator) : TypeNameNode(rhs, selfAllocator) {
}

XYLO_API U16TypeNameNode::~U16TypeNameNode() {
}

XYLO_API void U16TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<U16TypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> U32TypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<U32TypeNameNode> duplicatedNode(peff::allocAndConstruct<U32TypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API U32TypeNameNode::U32TypeNameNode(peff::Alloc *selfAllocator, Module *mod) : TypeNameNode(TypeNameKind::U32, selfAllocator, mod) {
}

XYLO_API U32TypeNameNode::U32TypeNameNode(const U32TypeNameNode &rhs, peff::Alloc *selfAllocator) : TypeNameNode(rhs, selfAllocator) {
}

XYLO_API U32TypeNameNode::~U32TypeNameNode() {
}

XYLO_API void U32TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<U32TypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> U64TypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<U64TypeNameNode> duplicatedNode(peff::allocAndConstruct<U64TypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API U64TypeNameNode::U64TypeNameNode(peff::Alloc *selfAllocator, Module *mod) : TypeNameNode(TypeNameKind::U64, selfAllocator, mod) {
}

XYLO_API U64TypeNameNode::U64TypeNameNode(const U64TypeNameNode &rhs, peff::Alloc *selfAllocator) : TypeNameNode(rhs, selfAllocator) {
}

XYLO_API U64TypeNameNode::~U64TypeNameNode() {
}

XYLO_API void U64TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<U64TypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> ISizeTypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<ISizeTypeNameNode> duplicatedNode(peff::allocAndConstruct<ISizeTypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API ISizeTypeNameNode::ISizeTypeNameNode(peff::Alloc *selfAllocator, Module *mod) : TypeNameNode(TypeNameKind::ISize, selfAllocator, mod) {
}

XYLO_API ISizeTypeNameNode::ISizeTypeNameNode(const ISizeTypeNameNode &rhs, peff::Alloc *selfAllocator) : TypeNameNode(rhs, selfAllocator) {
}

XYLO_API ISizeTypeNameNode::~ISizeTypeNameNode() {
}

XYLO_API void ISizeTypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<ISizeTypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> USizeTypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<USizeTypeNameNode> duplicatedNode(peff::allocAndConstruct<USizeTypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API USizeTypeNameNode::USizeTypeNameNode(peff::Alloc *selfAllocator, Module *mod) : TypeNameNode(TypeNameKind::USize, selfAllocator, mod) {
}

XYLO_API USizeTypeNameNode::USizeTypeNameNode(const USizeTypeNameNode &rhs, peff::Alloc *selfAllocator) : TypeNameNode(rhs, selfAllocator) {
}

XYLO_API USizeTypeNameNode::~USizeTypeNameNode() {
}

XYLO_API void USizeTypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<USizeTypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> F32TypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<F32TypeNameNode> duplicatedNode(peff::allocAndConstruct<F32TypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API F32TypeNameNode::F32TypeNameNode(peff::Alloc *selfAllocator, Module *mod) : TypeNameNode(TypeNameKind::F32, selfAllocator, mod) {
}

XYLO_API F32TypeNameNode::F32TypeNameNode(const F32TypeNameNode &rhs, peff::Alloc *selfAllocator) : TypeNameNode(rhs, selfAllocator) {
}

XYLO_API F32TypeNameNode::~F32TypeNameNode() {
}

XYLO_API void F32TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<F32TypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> F64TypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<F64TypeNameNode> duplicatedNode(peff::allocAndConstruct<F64TypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API F64TypeNameNode::F64TypeNameNode(peff::Alloc *selfAllocator, Module *mod) : TypeNameNode(TypeNameKind::F64, selfAllocator, mod) {
}

XYLO_API F64TypeNameNode::F64TypeNameNode(const F64TypeNameNode &rhs, peff::Alloc *selfAllocator) : TypeNameNode(rhs, selfAllocator) {
}

XYLO_API F64TypeNameNode::~F64TypeNameNode() {
}

XYLO_API void F64TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<F64TypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> StringTypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<StringTypeNameNode> duplicatedNode(peff::allocAndConstruct<StringTypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API StringTypeNameNode::StringTypeNameNode(peff::Alloc *selfAllocator, Module *mod) : TypeNameNode(TypeNameKind::String, selfAllocator, mod) {
}

XYLO_API StringTypeNameNode::StringTypeNameNode(const StringTypeNameNode &rhs, peff::Alloc *selfAllocator) : TypeNameNode(rhs, selfAllocator) {
}

XYLO_API StringTypeNameNode::~StringTypeNameNode() {
}

XYLO_API void StringTypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<StringTypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> BoolTypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	peff::RcObjectPtr<BoolTypeNameNode> duplicatedNode(peff::allocAndConstruct<BoolTypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator));
	if(!duplicatedNode) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API BoolTypeNameNode::BoolTypeNameNode(peff::Alloc *selfAllocator, Module *mod) : TypeNameNode(TypeNameKind::Bool, selfAllocator, mod) {
}

XYLO_API BoolTypeNameNode::BoolTypeNameNode(const BoolTypeNameNode &rhs, peff::Alloc *selfAllocator) : TypeNameNode(rhs, selfAllocator) {
}

XYLO_API BoolTypeNameNode::~BoolTypeNameNode() {
}

XYLO_API void BoolTypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<BoolTypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> CustomTypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<CustomTypeNameNode> duplicatedNode(peff::allocAndConstruct<CustomTypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator, succeeded));
	if((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API CustomTypeNameNode::CustomTypeNameNode(peff::Alloc *selfAllocator, Module *mod, IdRefPtr &&idRefPtr) : TypeNameNode(TypeNameKind::Custom, selfAllocator, mod), idRefPtr(std::move(idRefPtr)) {
}

XYLO_API CustomTypeNameNode::CustomTypeNameNode(const CustomTypeNameNode &rhs, peff::Alloc *allocator, bool &succeededOut) : TypeNameNode(rhs, allocator) {
	if(!(idRefPtr = duplicateIdRef(allocator, rhs.idRefPtr.get()))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

XYLO_API CustomTypeNameNode::~CustomTypeNameNode() {
}

XYLO_API void CustomTypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<CustomTypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> ExprTypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<ExprTypeNameNode> duplicatedNode(peff::allocAndConstruct<ExprTypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator, succeeded));
	if((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API ExprTypeNameNode::ExprTypeNameNode(peff::Alloc *selfAllocator, Module *mod, ExprNode *expr) : TypeNameNode(TypeNameKind::Expr, selfAllocator, mod), expr(expr) {
}

XYLO_API ExprTypeNameNode::ExprTypeNameNode(const ExprTypeNameNode &rhs, peff::Alloc *allocator, bool &succeededOut) : TypeNameNode(rhs, allocator) {
	if(!(expr = rhs.expr->duplicate<ExprNode>(allocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

XYLO_API ExprTypeNameNode::~ExprTypeNameNode() {
}

XYLO_API void ExprTypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<ExprTypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> ArrayTypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<ArrayTypeNameNode> duplicatedNode(peff::allocAndConstruct<ArrayTypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator, succeeded));
	if((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API ArrayTypeNameNode::ArrayTypeNameNode(peff::Alloc *selfAllocator, Module *mod, TypeNameNode *elementType) : TypeNameNode(TypeNameKind::Array, selfAllocator, mod), elementType(elementType) {
}

XYLO_API ArrayTypeNameNode::ArrayTypeNameNode(const ArrayTypeNameNode &rhs, peff::Alloc *allocator, bool &succeededOut) : TypeNameNode(rhs, allocator) {
	if(!(elementType = rhs.elementType->duplicate<TypeNameNode>(allocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

XYLO_API ArrayTypeNameNode::~ArrayTypeNameNode() {
}

XYLO_API void ArrayTypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<ArrayTypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> PointerTypeNameNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<PointerTypeNameNode> duplicatedNode(peff::allocAndConstruct<PointerTypeNameNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator, succeeded));
	if((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API PointerTypeNameNode::PointerTypeNameNode(peff::Alloc *selfAllocator, Module *mod, TypeNameNode *elementType) : TypeNameNode(TypeNameKind::Pointer, selfAllocator, mod), pointedType(pointedType) {
}

XYLO_API PointerTypeNameNode::PointerTypeNameNode(const PointerTypeNameNode &rhs, peff::Alloc *allocator, bool &succeededOut) : TypeNameNode(rhs, allocator) {
	if(!(pointedType = rhs.pointedType->duplicate<TypeNameNode>(allocator))) {
		succeededOut = false;
		return;
	}

	succeededOut = true;
}

XYLO_API PointerTypeNameNode::~PointerTypeNameNode() {
}

XYLO_API void PointerTypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<PointerTypeNameNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}
