#ifndef _XYLO_AST_IDREF_H_
#define _XYLO_AST_IDREF_H_

#include "typename_base.h"

namespace xylo {
	class TypeNameNode;

	class IdRef final {
	public:
		peff::RcObjectPtr<peff::Alloc> selfAllocator;
		peff::DynArray<peff::String> names;
		peff::DynArray<peff::RcObjectPtr<TypeNameNode>> genericArgs;

		XYLO_API IdRef(peff::Alloc *selfAllocator, peff::DynArray<peff::String> &&names = {}, peff::DynArray<peff::RcObjectPtr<TypeNameNode>> &&genericArgs = {});
		XYLO_API ~IdRef();

		XYLO_API void dealloc() noexcept;
	};

	using IdRefPtr = std::unique_ptr<IdRef, peff::DeallocableDeleter<IdRef>>;
}

#endif
