///
/// @file opcode.h
/// @author TrotVM Project
/// @brief Opcode definitions.
/// 
/// @copyright Copyright (c) 2025 TrotVM Project
///
#ifndef _TROTVM_OPCODE_H_
#define _TROTVM_OPCODE_H_

#include <cstdint>
#include <cstddef>

namespace trotvm {
    enum class Opcode : uint32_t {
        NOP = 0,

        LOAD,
        STORE,

        ADD,
        SUB,
        MUL,
        DIV,
        MOD,
        AND,
        OR,
        XOR,
        LAND,
        LOR,
        EQ,
        NEQ,
        LT,
        GT,
        LTEQ,
        GTEQ,
        SHFL,
        SHFR,
        ROTL,
        ROTR,
        CMP,
        
        NOT,
        LNOT,
        NEG,

        AT,

        JMP,
        JT,
        JF,

        PUSHARG,

        CALL,
        MCALL,
        RET,

        YIELD,

        LTHIS,
        
        STACKALLOC,
        LARG,
    };
}

#endif