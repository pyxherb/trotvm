#include "../parser.h"

using namespace xylo;

XYLO_API std::optional<SyntaxError> Parser::parseTypeName(peff::RcObjectPtr<TypeNameNode> &typeNameOut) {
	Token *t = peekToken();

	switch (t->tokenId) {
		case TokenId::VoidTypeName:
			typeNameOut->tokenRange = TokenRange{ t->index };
			if (!(typeNameOut = peff::allocAndConstruct<VoidTypeNameNode>(
					  resourceAllocator.get(),
					  sizeof(std::max_align_t),
					  resourceAllocator.get())))
				return genOutOfMemoryError();
			nextToken();
			break;
		case TokenId::I8TypeName:
			typeNameOut->tokenRange = TokenRange{ t->index };
			if (!(typeNameOut = peff::allocAndConstruct<I8TypeNameNode>(
					  resourceAllocator.get(),
					  sizeof(std::max_align_t),
					  resourceAllocator.get())))
				return genOutOfMemoryError();
			nextToken();
			break;
		case TokenId::I16TypeName:
			typeNameOut->tokenRange = TokenRange{ t->index };
			if (!(typeNameOut = peff::allocAndConstruct<I16TypeNameNode>(
					  resourceAllocator.get(),
					  sizeof(std::max_align_t),
					  resourceAllocator.get())))
				return genOutOfMemoryError();
			nextToken();
			break;
		case TokenId::I32TypeName:
			typeNameOut->tokenRange = TokenRange{ t->index };
			if (!(typeNameOut = peff::allocAndConstruct<I32TypeNameNode>(
					  resourceAllocator.get(),
					  sizeof(std::max_align_t),
					  resourceAllocator.get())))
				return genOutOfMemoryError();
			nextToken();
			break;
		case TokenId::I64TypeName:
			typeNameOut->tokenRange = TokenRange{ t->index };
			if (!(typeNameOut = peff::allocAndConstruct<I64TypeNameNode>(
					  resourceAllocator.get(),
					  sizeof(std::max_align_t),
					  resourceAllocator.get())))
				return genOutOfMemoryError();
			nextToken();
			break;
		case TokenId::U8TypeName:
			typeNameOut->tokenRange = TokenRange{ t->index };
			if (!(typeNameOut = peff::allocAndConstruct<U8TypeNameNode>(
					  resourceAllocator.get(),
					  sizeof(std::max_align_t),
					  resourceAllocator.get())))
				return genOutOfMemoryError();
			nextToken();
			break;
		case TokenId::U16TypeName:
			typeNameOut->tokenRange = TokenRange{ t->index };
			if (!(typeNameOut = peff::allocAndConstruct<U16TypeNameNode>(
					  resourceAllocator.get(),
					  sizeof(std::max_align_t),
					  resourceAllocator.get())))
				return genOutOfMemoryError();
			nextToken();
			break;
		case TokenId::U32TypeName:
			typeNameOut->tokenRange = TokenRange{ t->index };
			if (!(typeNameOut = peff::allocAndConstruct<U32TypeNameNode>(
					  resourceAllocator.get(),
					  sizeof(std::max_align_t),
					  resourceAllocator.get())))
				return genOutOfMemoryError();
			nextToken();
			break;
		case TokenId::U64TypeName:
			typeNameOut->tokenRange = TokenRange{ t->index };
			if (!(typeNameOut = peff::allocAndConstruct<U64TypeNameNode>(
					  resourceAllocator.get(),
					  sizeof(std::max_align_t),
					  resourceAllocator.get())))
				return genOutOfMemoryError();
			nextToken();
			break;
		case TokenId::ISizeTypeName:
			typeNameOut->tokenRange = TokenRange{ t->index };
			if (!(typeNameOut = peff::allocAndConstruct<ISizeTypeNameNode>(
					  resourceAllocator.get(),
					  sizeof(std::max_align_t),
					  resourceAllocator.get())))
				return genOutOfMemoryError();
			break;
		case TokenId::USizeTypeName:
			typeNameOut->tokenRange = TokenRange{ t->index };
			if (!(typeNameOut = peff::allocAndConstruct<USizeTypeNameNode>(
					  resourceAllocator.get(),
					  sizeof(std::max_align_t),
					  resourceAllocator.get())))
				return genOutOfMemoryError();
			nextToken();
			break;
		case TokenId::F32TypeName:
			typeNameOut->tokenRange = TokenRange{ t->index };
			if (!(typeNameOut = peff::allocAndConstruct<F32TypeNameNode>(
					  resourceAllocator.get(),
					  sizeof(std::max_align_t),
					  resourceAllocator.get())))
				return genOutOfMemoryError();
			nextToken();
			break;
		case TokenId::F64TypeName:
			typeNameOut->tokenRange = TokenRange{ t->index };
			if (!(typeNameOut = peff::allocAndConstruct<F64TypeNameNode>(
					  resourceAllocator.get(),
					  sizeof(std::max_align_t),
					  resourceAllocator.get())))
				return genOutOfMemoryError();
			nextToken();
			break;
		case TokenId::BoolTypeName:
			if (!(typeNameOut = peff::allocAndConstruct<BoolTypeNameNode>(
					  resourceAllocator.get(),
					  sizeof(std::max_align_t),
					  resourceAllocator.get())))
				return genOutOfMemoryError();
			typeNameOut->tokenRange = TokenRange{ t->index };
			nextToken();
			break;
		case TokenId::Id: {
			IdRefPtr id;
			XYLO_PARSER_RETURN_IF_ERROR(parseIdRef(id));
			typeNameOut->tokenRange = id->tokenRange;

			if (!(typeNameOut = peff::allocAndConstruct<CustomTypeNameNode>(
					  resourceAllocator.get(),
					  sizeof(std::max_align_t),
					  resourceAllocator.get(),
					  std::move(id))))
				return genOutOfMemoryError();
			break;
		}
		default:
			return SyntaxError(TokenRange{ t->index }, SyntaxErrorKind::UnexpectedToken);
	}

	while ((t = peekToken())->tokenId == TokenId::MulOp) {
		nextToken();
		if (!(typeNameOut = peff::allocAndConstruct<PointerTypeNameNode>(
				  resourceAllocator.get(),
				  sizeof(std::max_align_t),
				  resourceAllocator.get(),
				  typeNameOut.get())))
			return genOutOfMemoryError();
	}

	return {};
}
