#ifndef _CILVER_LEXER_H_
#define _CILVER_LEXER_H_

#include "basedefs.h"
#include <trotvm/vm.h>
#include <peff/base/deallocable.h>
#include <peff/containers/string.h>
#include <optional>

namespace cilver {
	struct SourcePosition {
		size_t line, column;

		TROTVM_FORCEINLINE SourcePosition() : line(SIZE_MAX), column(SIZE_MAX) {}
		TROTVM_FORCEINLINE SourcePosition(size_t line, size_t column) : line(line), column(column) {}

		TROTVM_FORCEINLINE bool operator<(const SourcePosition &loc) const {
			if (line < loc.line)
				return true;
			if (line > loc.line)
				return false;
			return column < loc.column;
		}

		TROTVM_FORCEINLINE bool operator>(const SourcePosition &loc) const {
			if (line > loc.line)
				return true;
			if (line < loc.line)
				return false;
			return column > loc.column;
		}

		TROTVM_FORCEINLINE bool operator==(const SourcePosition &loc) const {
			return (line == loc.line) && (column == loc.column);
		}

		TROTVM_FORCEINLINE bool operator>=(const SourcePosition &loc) const {
			return ((*this) == loc) || ((*this) > loc);
		}

		TROTVM_FORCEINLINE bool operator<=(const SourcePosition &loc) const {
			return ((*this) == loc) || ((*this) < loc);
		}
	};

	struct SourceLocation {
		SourcePosition beginPosition, endPosition;
	};

	class Lexer;

	enum class TokenId {
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

		LetKeyword,
		AsKeyword,
		IfKeyword,
		ElseKeyword,
		ReturnKeyword,
		ForKeyword,
		WhileKeyword,
		DoKeyword,
		StructKeyword,
		EnumKeyword,
		DeleteKeyword,
		FnKeyword,
		TemplateKeyword,
		TypenameKeyword,
		DeferKeyword,
		ImportKeyword,
		MacroKeyword,
		ExternKeyword,
		StaticKeyword,
	};

	class Token {
	public:
		TokenId tokenId;
		peff::RcObjectPtr<peff::Alloc> allocator;
		peff::String sourceText;

		KAST_API Token(peff::Alloc *allocator);
		KAST_API virtual ~Token();
	};

	using TokenList = peff::DynArray<std::unique_ptr<Token, peff::DeallocableDeleter<Token>>>;

	class Lexer {
	public:
	};
}

#endif
