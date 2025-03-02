#ifndef _KAST_AST_ASTNODE_H_
#define _KAST_AST_ASTNODE_H_

#include "lexer.h"

namespace kast {
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

		KAST_API AstNode(AstNodeType astNodeType);
		KAST_FORCEINLINE AstNode(const AstNode &other) {
			astNodeType = other.astNodeType;
			tokenRange = other.tokenRange;
		}
		KAST_FORCEINLINE virtual ~AstNode();

		template <typename T>
		KAST_FORCEINLINE peff::RcObjectPtr<T> duplicate() {
			return (T *)doDuplicate().get();
		}
	};
}

#endif
