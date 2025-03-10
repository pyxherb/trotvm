#include "../parser.h"

using namespace xylo;

#define GEN_BAD_EXPR_IF_ERROR(e) \
	if (auto _ = (e); _) goto genBadExpr

XYLO_API std::optional<SyntaxError> Parser::parseExpr(int precedence, ExprNode *&exprOut) {
	Token *prefixToken;

	peff::RcObjectPtr<ExprNode> lhs, rhs;

	GEN_BAD_EXPR_IF_ERROR(expectToken((prefixToken = peekToken())));

	switch (prefixToken->tokenId) {
		case TokenId::ThisKeyword:
		case TokenId::ScopeOp:
		case TokenId::Id: {
			IdRefPtr idRefPtr;
			GEN_BAD_EXPR_IF_ERROR(parseIdRef(idRefPtr));
			if (!(lhs = peff::allocAndConstruct<IdRefExprNode>(resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(), std::move(idRefPtr))))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::LParenthese: {
			nextToken();

			parseExpr(lhs.getRef());

			Token *rParentheseToken;

			GEN_BAD_EXPR_IF_ERROR(expectToken((rParentheseToken = nextToken()), TokenId::RParenthese));
			break;
		}
		case TokenId::IntLiteral: {
			if (!(lhs = peff::allocAndConstruct<I32LiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(),
					  ((IntTokenExtension *)prefixToken->exData.get())->data)))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::LongLiteral: {
			if (!(lhs = peff::allocAndConstruct<I64LiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(),
					  ((LongTokenExtension *)prefixToken->exData.get())->data)))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::UIntLiteral: {
			if (!(lhs = peff::allocAndConstruct<U32LiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(),
					  ((UIntTokenExtension *)prefixToken->exData.get())->data)))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::ULongLiteral: {
			if (!(lhs = peff::allocAndConstruct<U64LiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(),
					  ((ULongTokenExtension *)prefixToken->exData.get())->data)))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::StringLiteral: {
			peff::String s;

			if (!peff::copyAssign(s, ((StringTokenExtension *)prefixToken->exData.get())->data))
				return genOutOfMemoryError();

			if (!(lhs = peff::allocAndConstruct<StringLiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(),
					  std::move(s))))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::F32Literal: {
			if (!(lhs = peff::allocAndConstruct<F32LiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(),
					  ((F32TokenExtension *)prefixToken->exData.get())->data)))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::F64Literal: {
			if (!(lhs = peff::allocAndConstruct<F64LiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(),
					  ((F64TokenExtension *)prefixToken->exData.get())->data)))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::TrueKeyword: {
			if (!(lhs = peff::allocAndConstruct<BoolLiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(),
					  true)))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::FalseKeyword: {
			if (!(lhs = peff::allocAndConstruct<BoolLiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get(),
					  false)))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::NullptrKeyword: {
			if (!(lhs = peff::allocAndConstruct<NullptrLiteralExprNode>(
					  resourceAllocator.get(), sizeof(std::max_align_t), resourceAllocator.get())))
				return genOutOfMemoryError();
			break;
		}
		case TokenId::LBracket: {
			// TODO: Parse the initializer list.
		}
		case TokenId::LBrace: {
			// TODO: Parse the designated initializer.
		}
		default:
			nextToken();
			return SyntaxError(
				TokenRange{ prefixToken->index },
				SyntaxErrorKind::ExpectingExpr);
	}

genBadExpr:
}
