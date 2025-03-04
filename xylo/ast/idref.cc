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

XYLO_API IdRefPtr xylo::duplicateIdRef(peff::Alloc *selfAllocator, IdRef *rhs) {
	peff::DynArray<peff::String> copiedNames(selfAllocator);
	peff::DynArray<peff::RcObjectPtr<TypeNameNode>> copiedTypeNameNodes(selfAllocator);

	if(!copiedTypeNameNodes.resize(rhs->genericArgs.size())) {
		return {};
	}

	if(!peff::copyAssign(copiedNames, rhs->names)) {
		return {};
	}

	for(size_t i = 0 ; i < rhs->genericArgs.size(); ++i) {
		if(!(copiedTypeNameNodes.at(i) = rhs->genericArgs.at(i)->duplicate<TypeNameNode>(selfAllocator))) {
			return {};
		}
	}

	return IdRefPtr(
		peff::allocAndConstruct<IdRef>(
			selfAllocator,
			sizeof(std::max_align_t),
			selfAllocator,
			std::move(copiedNames),
			std::move(copiedTypeNameNodes)));
}
