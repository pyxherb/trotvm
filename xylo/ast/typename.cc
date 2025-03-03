#include "typename.h"

using namespace xylo;

XYLO_API VoidTypeNameNode::VoidTypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(TypeNameKind::Void, selfAllocator) {
}

XYLO_API VoidTypeNameNode::~VoidTypeNameNode() {
}

XYLO_API void VoidTypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<VoidTypeNameNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API I8TypeNameNode::I8TypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(TypeNameKind::I8, selfAllocator) {
}

XYLO_API I8TypeNameNode::~I8TypeNameNode() {
}

XYLO_API void I8TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<I8TypeNameNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API I16TypeNameNode::I16TypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(TypeNameKind::I16, selfAllocator) {
}

XYLO_API I16TypeNameNode::~I16TypeNameNode() {
}

XYLO_API void I16TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<I16TypeNameNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API I32TypeNameNode::I32TypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(TypeNameKind::I32, selfAllocator) {
}

XYLO_API I32TypeNameNode::~I32TypeNameNode() {
}

XYLO_API void I32TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<I32TypeNameNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API I64TypeNameNode::I64TypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(TypeNameKind::I64, selfAllocator) {
}

XYLO_API I64TypeNameNode::~I64TypeNameNode() {
}

XYLO_API void I64TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<I64TypeNameNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API U8TypeNameNode::U8TypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(TypeNameKind::U8, selfAllocator) {
}

XYLO_API U8TypeNameNode::~U8TypeNameNode() {
}

XYLO_API void U8TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<U8TypeNameNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API U16TypeNameNode::U16TypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(TypeNameKind::U16, selfAllocator) {
}

XYLO_API U16TypeNameNode::~U16TypeNameNode() {
}

XYLO_API void U16TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<U16TypeNameNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API U32TypeNameNode::U32TypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(TypeNameKind::U32, selfAllocator) {
}

XYLO_API U32TypeNameNode::~U32TypeNameNode() {
}

XYLO_API void U32TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<U32TypeNameNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API U64TypeNameNode::U64TypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(TypeNameKind::U64, selfAllocator) {
}

XYLO_API U64TypeNameNode::~U64TypeNameNode() {
}

XYLO_API void U64TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<U64TypeNameNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API F32TypeNameNode::F32TypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(TypeNameKind::F32, selfAllocator) {
}

XYLO_API F32TypeNameNode::~F32TypeNameNode() {
}

XYLO_API void F32TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<F32TypeNameNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API F64TypeNameNode::F64TypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(TypeNameKind::F64, selfAllocator) {
}

XYLO_API F64TypeNameNode::~F64TypeNameNode() {
}

XYLO_API void F64TypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<F64TypeNameNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API StringTypeNameNode::StringTypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(TypeNameKind::String, selfAllocator) {
}

XYLO_API StringTypeNameNode::~StringTypeNameNode() {
}

XYLO_API void StringTypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<StringTypeNameNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API BoolTypeNameNode::BoolTypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(TypeNameKind::Bool, selfAllocator) {
}

XYLO_API BoolTypeNameNode::~BoolTypeNameNode() {
}

XYLO_API void BoolTypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<BoolTypeNameNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API CustomTypeNameNode::CustomTypeNameNode(peff::Alloc *selfAllocator) : TypeNameNode(TypeNameKind::Custom, selfAllocator), path(selfAllocator), genericArgs(selfAllocator) {
}

XYLO_API CustomTypeNameNode::~CustomTypeNameNode() {
}

XYLO_API void CustomTypeNameNode::onRefZero() noexcept {
	peff::destroyAndRelease<CustomTypeNameNode>(selfAllocator.get(), this, sizeof(std::max_align_t));
}
