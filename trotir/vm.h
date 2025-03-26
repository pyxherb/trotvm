#ifndef _TROTIR_VM_H_
#define _TROTIR_VM_H_

#include "object.h"
#include <peff/containers/set.h>

namespace trotir {
	class VM {
	public:
		peff::RcObjectPtr<peff::Alloc> vmAlloc;
	};
}

#endif
