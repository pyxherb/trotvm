#ifndef _TROTVM_VM_H_
#define _TROTVM_VM_H_

#include "object.h"
#include <peff/containers/set.h>

namespace trotvm {
	class VM {
	public:
		peff::RcObjectPtr<peff::Alloc> vmAlloc;
	};
}

#endif
