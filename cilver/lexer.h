#ifndef _CILVER_LEXER_H_
#define _CILVER_LEXER_H_

#include "basedefs.h"
#include <trotir/irm.h>
#include <peff/containers/string.h>
#include <optional>

namespace cilver {
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

	};

	class Token {
	public:
		TokenId tokenId;
		peff::RcObjectPtr<peff::Alloc> allocator;
		peff::String sourceText;

		CILVER_API Token(peff::Alloc *allocator);
		CILVER_API virtual ~Token();
	};

	class Lexer {
	public:
		CILVER_API std::optional<peff::String> concatTrailingBackslashes(const std::string_view &src, peff::Alloc *allocator);
	};
}

#endif
