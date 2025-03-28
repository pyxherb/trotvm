#ifndef _TROTIR_PROC_H_
#define _TROTIR_PROC_H_

#include "value.h"
#include <peff/containers/dynarray.h>

namespace trotir {
	class Instruction {
	public:
		Opcode opcode;
		peff::DynArray<Value> operands;
	};

	class Fn {
	public:
		peff::DynArray<Instruction> instructions;
	};
}

#endif
