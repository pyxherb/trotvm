#ifndef _TROTIR_TYPE_H_
#define _TROTIR_TYPE_H_

#include <cstddef>

namespace trotir {
    enum class MajorType {
        Void,

        I8,
        I16,
        I32,
        I64,

        U8,
        U16,
        U32,
        U64,

        F32,
        F64,

        Bool,

        Array,
        Pointer,
		Vector,
		Matrix
    };

    class TypeDef;
    class VectorTypeDef;
    class MatrixTypeDef;

    struct Type {
        union {
            struct {
                TypeDef *typeDef;
            } asArray;
            struct {
                TypeDef *typeDef;
            } asPointer;
            struct {
                TypeDef *typeDef;
                size_t nDimensions;
            } asVector;
            struct {
                TypeDef *typeDef;
                size_t columns, rows;
            } asMatrix;
        } exData;
        MajorType majorType;
    };
}

#endif
