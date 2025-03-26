#ifndef _XYLO_AST_LEXER_H_
#define _XYLO_AST_LEXER_H_

#include "basedefs.h"
#include <trotir/vm.h>
#include <peff/base/deallocable.h>
#include <peff/containers/string.h>
#include <optional>
#include <variant>

namespace xylo {
	struct SourcePosition {
		size_t line, column;

		TROTIR_FORCEINLINE SourcePosition() : line(SIZE_MAX), column(SIZE_MAX) {}
		TROTIR_FORCEINLINE SourcePosition(size_t line, size_t column) : line(line), column(column) {}

		TROTIR_FORCEINLINE bool operator<(const SourcePosition &loc) const {
			if (line < loc.line)
				return true;
			if (line > loc.line)
				return false;
			return column < loc.column;
		}

		TROTIR_FORCEINLINE bool operator>(const SourcePosition &loc) const {
			if (line > loc.line)
				return true;
			if (line < loc.line)
				return false;
			return column > loc.column;
		}

		TROTIR_FORCEINLINE bool operator==(const SourcePosition &loc) const {
			return (line == loc.line) && (column == loc.column);
		}

		TROTIR_FORCEINLINE bool operator>=(const SourcePosition &loc) const {
			return ((*this) == loc) || ((*this) > loc);
		}

		TROTIR_FORCEINLINE bool operator<=(const SourcePosition &loc) const {
			return ((*this) == loc) || ((*this) < loc);
		}
	};

	struct SourceLocation {
		SourcePosition beginPosition, endPosition;
	};

	class Lexer;

	enum class TokenId {
		End = 0,

		Id,

		Comma,
		Question,
		Colon,
		Semicolon,
		LBracket,
		RBracket,
		LBrace,
		RBrace,
		LParenthese,
		RParenthese,
		At,
		Dot,
		VarArg,

		ScopeOp,
		MatchOp,
		LAndOp,
		LOrOp,
		AddOp,
		SubOp,
		MulOp,
		DivOp,
		ModOp,
		AndOp,
		OrOp,
		XorOp,
		LNotOp,
		NotOp,
		AssignOp,
		AddAssignOp,
		SubAssignOp,
		MulAssignOp,
		DivAssignOp,
		ModAssignOp,
		AndAssignOp,
		OrAssignOp,
		XorAssignOp,
		LshAssignOp,
		RshAssignOp,
		EqOp,
		NeqOp,
		LshOp,
		RshOp,
		LtEqOp,
		GtEqOp,
		LtOp,
		GtOp,
		DollarOp,

		VoidTypeName,
		I8TypeName,
		I16TypeName,
		I32TypeName,
		I64TypeName,
		U8TypeName,
		U16TypeName,
		U32TypeName,
		U64TypeName,
		ISizeTypeName,
		USizeTypeName,
		F32TypeName,
		F64TypeName,
		BoolTypeName,

		LetKeyword,
		AsKeyword,
		IfKeyword,
		ElseKeyword,
		SwitchKeyword,
		CaseKeyword,
		ReturnKeyword,
		ForKeyword,
		WhileKeyword,
		DoKeyword,
		StructKeyword,
		EnumKeyword,
		FnKeyword,
		TypenameKeyword,
		DeferKeyword,
		ImportKeyword,
		MacroKeyword,
		ExternKeyword,
		StaticKeyword,
		YieldKeyword,
		AwaitKeyword,
		AsyncKeyword,
		ConstKeyword,
		UsingKeyword,
		AliasKeyword,
		UnionKeyword,
		AttributeKeyword,
		ThisKeyword,
		SelfKeyword,
		ImplKeyword,
		DefKeyword,
		GotoKeyword,
		SizeofKeyword,
		NamespaceKeyword,
		MutableKeyword,
		VolatileKeyword,
		TrueKeyword,
		FalseKeyword,
		NullptrKeyword,

		IntLiteral,
		LongLiteral,
		UIntLiteral,
		ULongLiteral,
		F32Literal,
		F64Literal,
		StringLiteral,

		Whitespace,
		NewLine,
		LineComment,
		BlockComment,
		DocumentationComment,
	};

	class TokenExtension {
	public:
		XYLO_API virtual ~TokenExtension();

		virtual void dealloc() = 0;
	};

	class IntTokenExtension : public TokenExtension {
	public:
		int data;
		peff::RcObjectPtr<peff::Alloc> allocator;

		XYLO_API IntTokenExtension(peff::Alloc *allocator, int data);
		XYLO_API virtual ~IntTokenExtension();

		XYLO_API virtual void dealloc() override;
	};

	class UIntTokenExtension : public TokenExtension {
	public:
		unsigned int data;
		peff::RcObjectPtr<peff::Alloc> allocator;

		XYLO_API UIntTokenExtension(peff::Alloc *allocator, unsigned int data);
		XYLO_API virtual ~UIntTokenExtension();

		XYLO_API virtual void dealloc() override;
	};

	class LongTokenExtension : public TokenExtension {
	public:
		long long data;
		peff::RcObjectPtr<peff::Alloc> allocator;

		XYLO_API LongTokenExtension(peff::Alloc *allocator, long long data);
		XYLO_API virtual ~LongTokenExtension();

		XYLO_API virtual void dealloc() override;
	};

	class ULongTokenExtension : public TokenExtension {
	public:
		unsigned long long data;
		peff::RcObjectPtr<peff::Alloc> allocator;

		XYLO_API ULongTokenExtension(peff::Alloc *allocator, unsigned long long data);
		XYLO_API virtual ~ULongTokenExtension();

		XYLO_API virtual void dealloc() override;
	};

	class F32TokenExtension : public TokenExtension {
	public:
		float data;
		peff::RcObjectPtr<peff::Alloc> allocator;

		XYLO_API F32TokenExtension(peff::Alloc *allocator, float data);
		XYLO_API virtual ~F32TokenExtension();

		XYLO_API virtual void dealloc() override;
	};

	class F64TokenExtension : public TokenExtension {
	public:
		double data;
		peff::RcObjectPtr<peff::Alloc> allocator;

		XYLO_API F64TokenExtension(peff::Alloc *allocator, double data);
		XYLO_API virtual ~F64TokenExtension();

		XYLO_API virtual void dealloc() override;
	};

	class StringTokenExtension : public TokenExtension {
	public:
		peff::String data;
		peff::RcObjectPtr<peff::Alloc> allocator;

		XYLO_API StringTokenExtension(peff::Alloc *allocator, peff::String &&data);
		XYLO_API virtual ~StringTokenExtension();

		XYLO_API virtual void dealloc() override;
	};

	class Token {
	public:
		TokenId tokenId;
		peff::RcObjectPtr<peff::Alloc> allocator;
		std::string_view sourceText;
		SourceLocation sourceLocation;
		std::unique_ptr<TokenExtension, peff::DeallocableDeleter<TokenExtension>> exData;
		size_t index = SIZE_MAX;

		XYLO_API Token(peff::Alloc *allocator);
		XYLO_API virtual ~Token();

		XYLO_API void dealloc();
	};

	using OwnedTokenPtr = std::unique_ptr<Token, peff::DeallocableDeleter<Token>>;
	using TokenList = peff::DynArray<OwnedTokenPtr>;

	struct LexicalError {
		SourceLocation location;
		const char *message;
	};

	class Lexer {
	public:
		TokenList tokenList;
		std::optional<LexicalError> lexicalError;

		[[nodiscard]] XYLO_API std::optional<LexicalError> lex(const std::string_view &src, peff::Alloc *allocator);
	};

	XYLO_API const char *getTokenName(TokenId tokenId);
}

#endif
