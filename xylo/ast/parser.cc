#include "parser.h"

using namespace xylo;

XYLO_API Parser::Parser(TokenList &&tokenList, peff::Alloc *selfAllocator, peff::Alloc *resourceAllocator) : tokenList(std::move(tokenList)), selfAllocator(selfAllocator), resourceAllocator(resourceAllocator), syntaxErrors(resourceAllocator) {
}

XYLO_API std::optional<SyntaxError> Parser::parseIdRef(IdRefPtr &idRefOut) {
	IdRefPtr idRefPtr(peff::allocAndConstruct<IdRef>(resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get()));
	if (!idRefPtr)
		return genOutOfMemoryError();
	Token *t = peekToken();

	idRefPtr->tokenRange = TokenRange{ t->index };

	if (t->tokenId == TokenId::ThisKeyword) {
		IdRefEntry entry(resourceAllocator.get());
		peff::String idText(resourceAllocator.get());
		if (!idText.build("this")) {
			return genOutOfMemoryError();
		}

		entry.name = std::move(idText);
		entry.nameTokenIndex = t->index;

		if (!idRefPtr->entries.pushBack(std::move(entry)))
			return genOutOfMemoryError();

		if ((t = peekToken())->tokenId != TokenId::Dot) {
			goto end;
		}

		entry.accessOpTokenIndex = t->index;
		idRefPtr->tokenRange.endIndex = t->index;
	} else if (t->tokenId == TokenId::ScopeOp) {
		IdRefEntry entry(resourceAllocator.get());
		peff::String idText(resourceAllocator.get());

		entry.name = std::move(idText);

		entry.accessOpTokenIndex = t->index;

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
		entry.nameTokenIndex = t->index;
		idRefPtr->tokenRange.endIndex = t->index;

		if ((t = peekToken())->tokenId == TokenId::LtOp) {
			nextToken();

			for (;;) {
				peff::RcObjectPtr<TypeNameNode> genericArg;
				XYLO_PARSER_RETURN_IF_ERROR(parseTypeName(genericArg));

				if (!entry.genericArgs.pushBack(std::move(genericArg))) {
					return genOutOfMemoryError();
				}

				idRefPtr->tokenRange.endIndex = genericArg->tokenRange.endIndex;

				if ((t = peekToken())->tokenId != TokenId::Comma) {
					break;
				}

				idRefPtr->tokenRange.endIndex = t->index;

				nextToken();
			}
		}

		if (!idRefPtr->entries.pushBack(std::move(entry)))
			return genOutOfMemoryError();

		if ((t = peekToken())->tokenId != TokenId::Dot) {
			break;
		}

		entry.accessOpTokenIndex = t->index;
		idRefPtr->tokenRange.endIndex = t->index;

		nextToken();
	}

end:
	idRefOut = std::move(idRefPtr);

	return {};
}

[[nodiscard]] XYLO_API std::optional<SyntaxError> Parser::parseArgs(peff::DynArray<peff::RcObjectPtr<ExprNode>> &argsOut, peff::DynArray<size_t> &idxCommaTokensOut) {
	while (true) {
		if (peekToken()->tokenId == TokenId::RParenthese) {
			break;
		}

		peff::RcObjectPtr<ExprNode> arg;

		if(auto e = parseExpr(0, arg); e)
			return e;

		if(!argsOut.pushBack(std::move(arg)))
			return genOutOfMemoryError();

		if (peekToken()->tokenId != TokenId::Comma) {
			break;
		}

		Token *commaToken = nextToken();
		if(!idxCommaTokensOut.pushBack(+commaToken->index))
			return genOutOfMemoryError();
	}

	return {};
}