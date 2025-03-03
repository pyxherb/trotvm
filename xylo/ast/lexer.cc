#include "lexer.h"

using namespace xylo;

XYLO_API TokenExtension::~TokenExtension() {}

XYLO_API IntTokenExtension::IntTokenExtension(peff::Alloc *allocator, int data) : allocator(allocator), data(data) {
}
XYLO_API IntTokenExtension::~IntTokenExtension() {
}
XYLO_API void IntTokenExtension::dealloc() {
	peff::destroyAndRelease<IntTokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API UIntTokenExtension::UIntTokenExtension(peff::Alloc *allocator, unsigned int data) : allocator(allocator), data(data) {
}
XYLO_API UIntTokenExtension::~UIntTokenExtension() {
}
XYLO_API void UIntTokenExtension::dealloc() {
	peff::destroyAndRelease<UIntTokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API LongTokenExtension::LongTokenExtension(peff::Alloc *allocator, long long data) : allocator(allocator), data(data) {
}
XYLO_API LongTokenExtension::~LongTokenExtension() {
}
XYLO_API void LongTokenExtension::dealloc() {
	peff::destroyAndRelease<LongTokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API ULongTokenExtension::ULongTokenExtension(peff::Alloc *allocator, unsigned long long data) : allocator(allocator), data(data) {
}
XYLO_API ULongTokenExtension::~ULongTokenExtension() {
}
XYLO_API void ULongTokenExtension::dealloc() {
	peff::destroyAndRelease<ULongTokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API F32TokenExtension::F32TokenExtension(peff::Alloc *allocator, float data) : allocator(allocator), data(data) {
}
XYLO_API F32TokenExtension::~F32TokenExtension() {
}
XYLO_API void F32TokenExtension::dealloc() {
	peff::destroyAndRelease<F32TokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API F64TokenExtension::F64TokenExtension(peff::Alloc *allocator, double data) : allocator(allocator), data(data) {
}
XYLO_API F64TokenExtension::~F64TokenExtension() {
}
XYLO_API void F64TokenExtension::dealloc() {
	peff::destroyAndRelease<F64TokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API StringTokenExtension::StringTokenExtension(peff::Alloc *allocator, peff::String &&data) : allocator(allocator), data(std::move(data)) {
}
XYLO_API StringTokenExtension::~StringTokenExtension() {
}
XYLO_API void StringTokenExtension::dealloc() {
	peff::destroyAndRelease<StringTokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API Token::Token(peff::Alloc* allocator) : allocator(allocator) {
}
XYLO_API Token::~Token() {
}
XYLO_API void Token::dealloc() {
	peff::destroyAndRelease<Token>(allocator.get(), this, sizeof(std::max_align_t));
}
