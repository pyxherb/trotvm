#ifndef _TROTVM_TYPE_H_
#define _TROTVM_TYPE_H_

#include <cstddef>

namespace trotvm {
    enum class MajorType {
        Void,

        I8,
        I16,
        I32,
        I64,
        I128,

        U8,
        U16,
        U32,
        U64,
        U128,
        
        F16,
        F32,
        F64,
        F128,
        
        Bool,

        Array,
        Pointer,
        /// @brief Tensor is used for n-dimensioned compound types such as vector, matrix, etc.
        Tensor
    };

    class TypeDef;
    class TensorTypeDef;

    struct Type {
        union {
            struct {
                TypeDef *typeDef;
            } asArray;
            struct {
                TypeDef *typeDef;
            } asPointer;
            struct {
                TensorTypeDef *typeDef;
                size_t nDimensions;
            } asTensor;
        } exData;
        MajorType majorType;
    };
}

#endif