#ifndef _TROTVM_VMOBJECT_H_
#define _TROTVM_VMOBJECT_H_

#include "basedefs.h"

namespace trotvm {
	class VM;

	class VMObject {
	public:
		const VM *associatedVm;

		TROTVM_API VMObject(VM *associatedVm) noexcept;
		virtual void dealloc() noexcept = 0;
	};
}

#endif
