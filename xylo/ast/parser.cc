#include "parser.h"

using namespace xylo;

XYLO_API Parser::Parser(TokenList &&tokenList, peff::Alloc *selfAllocator, peff::Alloc *resourceAllocator) : tokenList(std::move(tokenList)), selfAllocator(selfAllocator), resourceAllocator(resourceAllocator), syntaxErrors(resourceAllocator) {
}

XYLO_API std::optional<SyntaxError> Parser::parseIdRef(IdRefPtr &idRefOut) {
	IdRefPtr idRefPtr(peff::allocAndConstruct<IdRef>(resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get()));
	if (!idRefPtr)
		return genOutOfMemoryError();
	Token *t;

	if ((t = peekToken())->tokenId == TokenId::ThisKeyword) {
		IdRefEntry entry(resourceAllocator.get());
		peff::String idText(resourceAllocator.get());
		if (!idText.build("this")) {
			return genOutOfMemoryError();
		}

		entry.name = std::move(idText);

		if (!idRefPtr->entries.pushBack(std::move(entry)))
			return genOutOfMemoryError();

		if ((t = peekToken())->tokenId != TokenId::Dot) {
			goto end;
		}
	} else if ((t = peekToken())->tokenId == TokenId::ScopeOp) {
		IdRefEntry entry(resourceAllocator.get());
		peff::String idText(resourceAllocator.get());

		entry.name = std::move(idText);

		if (!idRefPtr->entries.pushBack(std::move(entry)))
			return genOutOfMemoryError();
	}

	for (;;) {
		XYLO_PARSER_RETURN_IF_ERROR(expectToken(t = nextToken(), TokenId::Id));

		IdRefEntry entry(resourceAllocator.get());
		peff::String idText(resourceAllocator.get());
		if (!idText.build(t->sourceText)) {
			return genOutOfMemoryError();
		}

		entry.name = std::move(idText);

		if ((t = peekToken())->tokenId == TokenId::LtOp) {
			nextToken();

			for (;;) {
				peff::RcObjectPtr<TypeNameNode> genericArg;
				XYLO_PARSER_RETURN_IF_ERROR(parseTypeName(genericArg));

				if (!entry.genericArgs.pushBack(std::move(genericArg))) {
					return genOutOfMemoryError();
				}

				if ((t = peekToken())->tokenId != TokenId::Comma) {
					break;
				}

				nextToken();
			}
		}

		if (!idRefPtr->entries.pushBack(std::move(entry)))
			return genOutOfMemoryError();

		if ((t = peekToken())->tokenId != TokenId::Dot) {
			break;
		}

		nextToken();
	}

end:
	idRefOut = std::move(idRefPtr);

	return {};
}
