#include "lexer.h"

using namespace cilver;

CILVER_API Token::Token(peff::Alloc *allocator) : allocator(allocator) {}
CILVER_API Token::~Token() {}

CILVER_API std::optional<peff::String> Lexer::concatTrailingBackslashes(const std::string_view &src, peff::Alloc *allocator) {
	peff::String s(allocator);

	size_t lastIdx = 0, idx;
	for (;;) {
		if (((idx = src.find("\\\n", lastIdx)) != std::string::npos)) {
			std::string_view newContents = src.substr(lastIdx, idx - lastIdx);
			if (!s.append(newContents.data(), newContents.size()))
				return {};
			lastIdx = idx + sizeof("\\\n");
		} else {
			break;
		}
	}

	return { std::move(s) };
}
