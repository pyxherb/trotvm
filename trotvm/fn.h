#ifndef _TROTVM_PROC_H_
#define _TROTVM_PROC_H_

#include "value.h"
#include <peff/containers/dynarray.h>

namespace trotvm {
	struct Instruction {
		Opcode opcode;
		peff::DynArray<Value> operands;
	};

    class Fn {
    public:
		peff::DynArray<Instruction> instructions;
    };
}

#endif
