#ifndef _XYLO_AST_IDREF_H_
#define _XYLO_AST_IDREF_H_

#include "typename_base.h"

namespace xylo {
	struct IdRefEntry {
		peff::String name;
		peff::DynArray<peff::RcObjectPtr<TypeNameNode>> genericArgs;
		size_t accessOpTokenIndex = SIZE_MAX, nameTokenIndex = SIZE_MAX, leftAngleBracketTokenIndex = SIZE_MAX, rightAngleBracketTokenIndex = SIZE_MAX;
		peff::DynArray<size_t> commaTokenIndices;

		XYLO_FORCEINLINE IdRefEntry(peff::Alloc *selfAllocator): name(selfAllocator), genericArgs(selfAllocator), commaTokenIndices(selfAllocator) {}
	};

	XYLO_API std::optional<IdRefEntry> duplicateIdRefEntry(peff::Alloc *selfAllocator, const IdRefEntry &rhs);

	class IdRef final {
	public:
		peff::RcObjectPtr<peff::Alloc> selfAllocator;
		peff::DynArray<IdRefEntry> entries;
		peff::RcObjectPtr<Module> mod;
		TokenRange tokenRange;

		XYLO_API IdRef(peff::Alloc *selfAllocator, Module *mod);
		XYLO_API ~IdRef();

		XYLO_API void dealloc() noexcept;
	};

	using IdRefPtr = std::unique_ptr<IdRef, peff::DeallocableDeleter<IdRef>>;

	XYLO_API IdRefPtr duplicateIdRef(peff::Alloc *selfAllocator, IdRef *rhs);
}

#endif
