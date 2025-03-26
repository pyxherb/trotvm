#ifndef _XYLO_AST_ASTNODE_H_
#define _XYLO_AST_ASTNODE_H_

#include "lexer.h"
#include <peff/base/rcobj.h>

namespace xylo {
	enum class AstNodeType : uint8_t {
		Class = 0,
		Struct,
		Union,
		Enum,
		EnumItem,
		Attribute,
		AttributeItem,
		Macro,
		Fn,
		Stmt,
		MetaStmt,
		Expr,
		MetaExpr,
		TypeName,
		MetaTypeName,
		Using,
		Var,
		GenericParam,

		Root,

		Bad
	};

	struct TokenRange {
		size_t beginIndex = SIZE_MAX, endIndex = SIZE_MAX;

		inline TokenRange() = default;
		inline TokenRange(size_t index) : beginIndex(index), endIndex(index) {}
		inline TokenRange(size_t beginIndex, size_t endIndex) : beginIndex(beginIndex), endIndex(endIndex) {}

		TROTIR_FORCEINLINE operator bool() {
			return beginIndex != SIZE_MAX;
		}
	};

	class AstNode : public peff::RcObject {
	protected:
		virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const;

	public:
		peff::RcObjectPtr<peff::Alloc> selfAllocator;
		AstNodeType astNodeType;
		TokenRange tokenRange;

		XYLO_API AstNode(AstNodeType astNodeType, peff::Alloc *selfAllocator);
		XYLO_FORCEINLINE AstNode(const AstNode &other, peff::Alloc *allocator) {
			astNodeType = other.astNodeType;
			tokenRange = other.tokenRange;
			selfAllocator = allocator;
		}
		XYLO_API virtual ~AstNode();

		template <typename T>
		XYLO_FORCEINLINE peff::RcObjectPtr<T> duplicate(peff::Alloc *newAllocator) const {
			return (T *)doDuplicate(newAllocator).get();
		}
	};
}

#endif
