#ifndef _TROTIR_VALUE_H_
#define _TROTIR_VALUE_H_

#include "opcode.h"

namespace trotir {
    enum class ValueType {
        I8,
        I16,
        I32,
        I64,
        U8,
        U16,
        U32,
        U64,
        F16,
        F32,
        F64,
        Bool,
        RegRef,
		LabelRef
    };

    struct Value {
        union {
            int8_t asI8;
            int16_t asI16;
            int32_t asI32;
            int64_t asI64;
            uint8_t asU8;
            uint16_t asU16;
            uint32_t asU32;
            uint64_t asU64;
            uint32_t asF32;
            uint64_t asF64;
            bool asBool;
        } data;
        ValueType valueType;
    };
}

#endif
