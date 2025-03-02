#include "lexer.h"

using namespace kast;

KAST_API TokenExtension::~TokenExtension() {}

KAST_API IntTokenExtension::IntTokenExtension(peff::Alloc *allocator, int data) : allocator(allocator), data(data) {
}
KAST_API IntTokenExtension::~IntTokenExtension() {
}
KAST_API void IntTokenExtension::dealloc() {
	peff::destroyAndRelease<IntTokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

KAST_API UIntTokenExtension::UIntTokenExtension(peff::Alloc *allocator, unsigned int data) : allocator(allocator), data(data) {
}
KAST_API UIntTokenExtension::~UIntTokenExtension() {
}
KAST_API void UIntTokenExtension::dealloc() {
	peff::destroyAndRelease<UIntTokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

KAST_API LongTokenExtension::LongTokenExtension(peff::Alloc *allocator, long long data) : allocator(allocator), data(data) {
}
KAST_API LongTokenExtension::~LongTokenExtension() {
}
KAST_API void LongTokenExtension::dealloc() {
	peff::destroyAndRelease<LongTokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

KAST_API ULongTokenExtension::ULongTokenExtension(peff::Alloc *allocator, unsigned long long data) : allocator(allocator), data(data) {
}
KAST_API ULongTokenExtension::~ULongTokenExtension() {
}
KAST_API void ULongTokenExtension::dealloc() {
	peff::destroyAndRelease<ULongTokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

KAST_API F32TokenExtension::F32TokenExtension(peff::Alloc *allocator, float data) : allocator(allocator), data(data) {
}
KAST_API F32TokenExtension::~F32TokenExtension() {
}
KAST_API void F32TokenExtension::dealloc() {
	peff::destroyAndRelease<F32TokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

KAST_API F64TokenExtension::F64TokenExtension(peff::Alloc *allocator, double data) : allocator(allocator), data(data) {
}
KAST_API F64TokenExtension::~F64TokenExtension() {
}
KAST_API void F64TokenExtension::dealloc() {
	peff::destroyAndRelease<F64TokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

KAST_API StringTokenExtension::StringTokenExtension(peff::Alloc *allocator, peff::String &&data) : allocator(allocator), data(std::move(data)) {
}
KAST_API StringTokenExtension::~StringTokenExtension() {
}
KAST_API void StringTokenExtension::dealloc() {
	peff::destroyAndRelease<StringTokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

KAST_API void Token::dealloc() {
	peff::destroyAndRelease<Token>(allocator.get(), this, sizeof(std::max_align_t));
}
