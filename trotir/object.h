#ifndef _TROTIR_VMOBJECT_H_
#define _TROTIR_VMOBJECT_H_

#include "basedefs.h"

namespace trotir {
	class VM;

	class VMObject {
	public:
		const VM *associatedVm;

		TROTIR_API VMObject(VM *associatedVm) noexcept;
		virtual void dealloc() noexcept = 0;
	};
}

#endif
