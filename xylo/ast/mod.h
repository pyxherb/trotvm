#ifndef _XYLO_AST_MODULE_H_
#define _XYLO_AST_MODULE_H_

#include "basedefs.h"
#include <peff/base/rcobj.h>
#include <peff/base/alloc.h>

namespace xylo {
	class Module : public peff::RcObject {
	public:
		peff::RcObjectPtr<peff::Alloc> selfAllocator;

		virtual void onRefZero() noexcept override;
	};
}

#endif