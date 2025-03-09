#include "idref.h"

using namespace xylo;

XYLO_API IdRef::IdRef(
	peff::Alloc *selfAllocator)
	: selfAllocator(selfAllocator),
	  entries(selfAllocator) {
}

XYLO_API IdRef::~IdRef() {
}

XYLO_API void IdRef::dealloc() noexcept {
	peff::destroyAndRelease<IdRef>(selfAllocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API std::optional<IdRefEntry> xylo::duplicateIdRefEntry(peff::Alloc *selfAllocator, const IdRefEntry &rhs) {
	IdRefEntry newIdRefEntry(selfAllocator);

	if (!newIdRefEntry.genericArgs.resize(rhs.genericArgs.size())) {
		return {};
	}

	for (size_t i = 0; i < rhs.genericArgs.size(); ++i) {
		if (!(newIdRefEntry.genericArgs.at(i) = rhs.genericArgs.at(i)->duplicate<TypeNameNode>(selfAllocator)))
			return {};
	}

	if (!newIdRefEntry.name.build(rhs.name)) {
		return {};
	}

	return std::move(newIdRefEntry);
}

XYLO_API IdRefPtr xylo::duplicateIdRef(peff::Alloc *selfAllocator, IdRef *rhs) {
	IdRefPtr newIdRefPtr = IdRefPtr(
		peff::allocAndConstruct<IdRef>(
			selfAllocator,
			sizeof(std::max_align_t),
			selfAllocator));

	if (!newIdRefPtr->entries.resize(rhs->entries.size())) {
		return {};
	}

	for (size_t i = 0; i < rhs->entries.size(); ++i) {
		std::optional<IdRefEntry> duplicatedEntry = duplicateIdRefEntry(selfAllocator, rhs->entries.at(i));

		if (!duplicatedEntry.has_value())
			return {};

		newIdRefPtr->entries.at(i) = std::move(*duplicatedEntry);
		duplicatedEntry.reset();
	}

	return newIdRefPtr;
}
