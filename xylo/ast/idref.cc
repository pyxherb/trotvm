#include "idref.h"

using namespace xylo;

XYLO_API IdRef::IdRef(
	peff::Alloc *selfAllocator,
	peff::DynArray<peff::String> &&names,
	peff::DynArray<peff::RcObjectPtr<TypeNameNode>> &&genericArgs)
	: selfAllocator(selfAllocator),
	  names(std::move(names)),
	  genericArgs(std::move(genericArgs)) {
}

XYLO_API IdRef::~IdRef() {
}

XYLO_API void IdRef::dealloc() noexcept {
	peff::destroyAndRelease<IdRef>(selfAllocator.get(), this, sizeof(std::max_align_t));
}
