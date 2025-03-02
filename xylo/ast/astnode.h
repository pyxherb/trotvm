#ifndef _XYLO_AST_ASTNODE_H_
#define _XYLO_AST_ASTNODE_H_

#include "lexer.h"

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

		TROTVM_FORCEINLINE operator bool() {
			return beginIndex != SIZE_MAX;
		}
	};

	class AstNode : public peff::RcObject {
	private:
		virtual peff::RcObjectPtr<AstNode> doDuplicate();

	public:
		AstNodeType astNodeType;
		TokenRange tokenRange;

		XYLO_API AstNode(AstNodeType astNodeType);
		XYLO_FORCEINLINE AstNode(const AstNode &other) {
			astNodeType = other.astNodeType;
			tokenRange = other.tokenRange;
		}
		XYLO_FORCEINLINE virtual ~AstNode();

		template <typename T>
		XYLO_FORCEINLINE peff::RcObjectPtr<T> duplicate() {
			return (T *)doDuplicate().get();
		}
	};
}

#endif
