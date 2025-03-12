#include <xylo/ast/lexer.h>

using namespace xylo;

enum LexCondition {
	yycInitialCondition = 0,

	yycStringCondition,
	yycEscapeCondition,

	yycCommentCondition,
	yycLineCommentCondition,
};

XYLO_API std::optional<LexicalError> Lexer::lex(const std::string_view &src, peff::Alloc *allocator) {
	const char *YYCURSOR = src.data(), *YYMARKER = YYCURSOR, *YYLIMIT = src.data() + src.size();
	const char *prevYYCURSOR = YYCURSOR;

	LexCondition YYCONDITION = yycInitialCondition;

#define YYSETCONDITION(cond) (YYCONDITION = (yyc##cond))
#define YYGETCONDITION() (YYCONDITION)

	OwnedTokenPtr token;

	while (true) {
		peff::String strLiteral(allocator);

		if (!(token = OwnedTokenPtr(peff::allocAndConstruct<Token>(allocator, sizeof(std::max_align_t), allocator))))
			goto outOfMemory;

		while (true) {
			/*!re2c
				re2c:yyfill:enable = 0;
				re2c:define:YYCTYPE = char;

				<InitialCondition>"///"		{ YYSETCONDITION(LineCommentCondition); token->tokenId = TokenId::DocumentationComment; continue; }
				<InitialCondition>"//"		{ YYSETCONDITION(LineCommentCondition); token->tokenId = TokenId::LineComment; continue; }
				<InitialCondition>"/*"		{ YYSETCONDITION(CommentCondition); token->tokenId = TokenId::BlockComment; continue; }

				<InitialCondition>"::"		{ token->tokenId = TokenId::ScopeOp; break; }
				<InitialCondition>"=>"		{ token->tokenId = TokenId::MatchOp; break; }
				<InitialCondition>"&&"		{ token->tokenId = TokenId::LAndOp; break; }
				<InitialCondition>"||"		{ token->tokenId = TokenId::LOrOp; break; }
				<InitialCondition>"+"		{ token->tokenId = TokenId::AddOp; break; }
				<InitialCondition>"-"		{ token->tokenId = TokenId::SubOp; break; }
				<InitialCondition>"*"		{ token->tokenId = TokenId::MulOp; break; }
				<InitialCondition>"/"		{ token->tokenId = TokenId::DivOp; break; }
				<InitialCondition>"%"		{ token->tokenId = TokenId::ModOp; break; }
				<InitialCondition>"&"		{ token->tokenId = TokenId::AndOp; break; }
				<InitialCondition>"|"		{ token->tokenId = TokenId::OrOp; break; }
				<InitialCondition>"^"		{ token->tokenId = TokenId::XorOp; break; }
				<InitialCondition>"!"		{ token->tokenId = TokenId::LNotOp; break; }
				<InitialCondition>"~"		{ token->tokenId = TokenId::NotOp; break; }
				<InitialCondition>"="		{ token->tokenId = TokenId::AssignOp; break; }
				<InitialCondition>"+="		{ token->tokenId = TokenId::AddAssignOp; break; }
				<InitialCondition>"-="		{ token->tokenId = TokenId::SubAssignOp; break; }
				<InitialCondition>"*="		{ token->tokenId = TokenId::MulAssignOp; break; }
				<InitialCondition>"/="		{ token->tokenId = TokenId::DivAssignOp; break; }
				<InitialCondition>"%="		{ token->tokenId = TokenId::ModAssignOp; break; }
				<InitialCondition>"&="		{ token->tokenId = TokenId::AndAssignOp; break; }
				<InitialCondition>"|="		{ token->tokenId = TokenId::OrAssignOp; break; }
				<InitialCondition>"^="		{ token->tokenId = TokenId::XorAssignOp; break; }
				<InitialCondition>"<<="		{ token->tokenId = TokenId::LshAssignOp; break; }
				<InitialCondition>">>="		{ token->tokenId = TokenId::RshAssignOp; break; }
				<InitialCondition>"=="		{ token->tokenId = TokenId::EqOp; break; }
				<InitialCondition>"!="		{ token->tokenId = TokenId::NeqOp; break; }
				<InitialCondition>"<<"		{ token->tokenId = TokenId::LshOp; break; }
				<InitialCondition>">>"		{ token->tokenId = TokenId::RshOp; break; }
				<InitialCondition>"<="		{ token->tokenId = TokenId::LtEqOp; break; }
				<InitialCondition>">="		{ token->tokenId = TokenId::GtEqOp; break; }
				<InitialCondition>"<"		{ token->tokenId = TokenId::LtOp; break; }
				<InitialCondition>">"		{ token->tokenId = TokenId::GtOp; break; }
				<InitialCondition>"$"		{ token->tokenId = TokenId::DollarOp; break; }

				<InitialCondition>"let"			{ token->tokenId = TokenId::LetKeyword; break; }
				<InitialCondition>"as"			{ token->tokenId = TokenId::AsKeyword; break; }
				<InitialCondition>"if"			{ token->tokenId = TokenId::IfKeyword; break; }
				<InitialCondition>"else"		{ token->tokenId = TokenId::ElseKeyword; break; }
				<InitialCondition>"switch"		{ token->tokenId = TokenId::SwitchKeyword; break; }
				<InitialCondition>"case"		{ token->tokenId = TokenId::CaseKeyword; break; }
				<InitialCondition>"return"		{ token->tokenId = TokenId::ReturnKeyword; break; }
				<InitialCondition>"for"			{ token->tokenId = TokenId::ForKeyword; break; }
				<InitialCondition>"while"		{ token->tokenId = TokenId::WhileKeyword; break; }
				<InitialCondition>"do"			{ token->tokenId = TokenId::DoKeyword; break; }
				<InitialCondition>"struct"		{ token->tokenId = TokenId::StructKeyword; break; }
				<InitialCondition>"enum"		{ token->tokenId = TokenId::EnumKeyword; break; }
				<InitialCondition>"fn"			{ token->tokenId = TokenId::FnKeyword; break; }
				<InitialCondition>"typename"	{ token->tokenId = TokenId::TypenameKeyword; break; }
				<InitialCondition>"defer"		{ token->tokenId = TokenId::DeferKeyword; break; }
				<InitialCondition>"import"		{ token->tokenId = TokenId::ImportKeyword; break; }
				<InitialCondition>"macro"		{ token->tokenId = TokenId::MacroKeyword; break; }
				<InitialCondition>"extern"		{ token->tokenId = TokenId::ExternKeyword; break; }
				<InitialCondition>"static"		{ token->tokenId = TokenId::StaticKeyword; break; }
				<InitialCondition>"yield"		{ token->tokenId = TokenId::YieldKeyword; break; }
				<InitialCondition>"await"		{ token->tokenId = TokenId::AwaitKeyword; break; }
				<InitialCondition>"async"		{ token->tokenId = TokenId::AsyncKeyword; break; }
				<InitialCondition>"const"		{ token->tokenId = TokenId::ConstKeyword; break; }
				<InitialCondition>"using"		{ token->tokenId = TokenId::UsingKeyword; break; }
				<InitialCondition>"alias"		{ token->tokenId = TokenId::AliasKeyword; break; }
				<InitialCondition>"union"		{ token->tokenId = TokenId::UnionKeyword; break; }
				<InitialCondition>"attribute"	{ token->tokenId = TokenId::AttributeKeyword; break; }
				<InitialCondition>"this"		{ token->tokenId = TokenId::ThisKeyword; break; }
				<InitialCondition>"self"		{ token->tokenId = TokenId::SelfKeyword; break; }
				<InitialCondition>"impl"		{ token->tokenId = TokenId::ImplKeyword; break; }
				<InitialCondition>"def"			{ token->tokenId = TokenId::DefKeyword; break; }
				<InitialCondition>"goto"		{ token->tokenId = TokenId::GotoKeyword; break; }
				<InitialCondition>"sizeof"		{ token->tokenId = TokenId::SizeofKeyword; break; }
				<InitialCondition>"namespace"	{ token->tokenId = TokenId::NamespaceKeyword; break; }
				<InitialCondition>"mutable"		{ token->tokenId = TokenId::MutableKeyword; break; }
				<InitialCondition>"volatile"	{ token->tokenId = TokenId::VolatileKeyword; break; }
				<InitialCondition>"true"		{ token->tokenId = TokenId::TrueKeyword; break; }
				<InitialCondition>"false"		{ token->tokenId = TokenId::FalseKeyword; break; }
				<InitialCondition>"nullptr"		{ token->tokenId = TokenId::NullptrKeyword; break; }

				<InitialCondition>"i8"			{ token->tokenId = TokenId::I8TypeName; break; }
				<InitialCondition>"i16"			{ token->tokenId = TokenId::I16TypeName; break; }
				<InitialCondition>"i32"			{ token->tokenId = TokenId::I32TypeName; break; }
				<InitialCondition>"i64"			{ token->tokenId = TokenId::I64TypeName; break; }
				<InitialCondition>"u8"			{ token->tokenId = TokenId::U8TypeName; break; }
				<InitialCondition>"u16"			{ token->tokenId = TokenId::U16TypeName; break; }
				<InitialCondition>"u32"			{ token->tokenId = TokenId::U32TypeName; break; }
				<InitialCondition>"u64"			{ token->tokenId = TokenId::U64TypeName; break; }
				<InitialCondition>"f32"			{ token->tokenId = TokenId::F32TypeName; break; }
				<InitialCondition>"f64"			{ token->tokenId = TokenId::F64TypeName; break; }
				<InitialCondition>"bool"		{ token->tokenId = TokenId::BoolTypeName; break; }
				<InitialCondition>"void"		{ token->tokenId = TokenId::VoidTypeName; break; }

				<InitialCondition>","		{ token->tokenId = TokenId::Comma; break; }
				<InitialCondition>"?"		{ token->tokenId = TokenId::Question; break; }
				<InitialCondition>":"		{ token->tokenId = TokenId::Colon; break; }
				<InitialCondition>";"     	{ token->tokenId = TokenId::Semicolon; break; }
				<InitialCondition>"["		{ token->tokenId = TokenId::LBracket; break; }
				<InitialCondition>"]"		{ token->tokenId = TokenId::RBracket; break; }
				<InitialCondition>"{"		{ token->tokenId = TokenId::LBrace; break; }
				<InitialCondition>"}"		{ token->tokenId = TokenId::RBrace; break; }
				<InitialCondition>"("		{ token->tokenId = TokenId::LParenthese; break; }
				<InitialCondition>")"		{ token->tokenId = TokenId::RParenthese; break; }
				<InitialCondition>"..."		{ token->tokenId = TokenId::VarArg; break; }
				<InitialCondition>"."		{ token->tokenId = TokenId::Dot; break; }

				<InitialCondition>[a-zA-Z_][a-zA-Z0-9_]* {
					token->tokenId = TokenId::Id;
					break;
				}

				<InitialCondition>"0"[0-7]+ {
					token->tokenId = TokenId::UIntLiteral;
					token->exData = std::unique_ptr<TokenExtension, peff::DeallocableDeleter<TokenExtension>>(
						peff::allocAndConstruct<UIntTokenExtension>(allocator, sizeof(std::max_align_t), allocator, strtoul(prevYYCURSOR, nullptr, 8)));
					break;
				}

				<InitialCondition>[0-9]+ {
					token->tokenId = TokenId::IntLiteral;
					token->exData = std::unique_ptr<TokenExtension, peff::DeallocableDeleter<TokenExtension>>(
						peff::allocAndConstruct<IntTokenExtension>(allocator, sizeof(std::max_align_t), allocator, strtol(prevYYCURSOR, nullptr, 10)));
					break;
				}

				<InitialCondition>"0"[xX][0-9a-fA-F]+ {
					token->tokenId = TokenId::UIntLiteral;
					token->exData = std::unique_ptr<TokenExtension, peff::DeallocableDeleter<TokenExtension>>(
						peff::allocAndConstruct<UIntTokenExtension>(allocator, sizeof(std::max_align_t), allocator, strtoul(prevYYCURSOR, nullptr, 16)));
					break;
				}

				<InitialCondition>"0"[bB][01]+ {
					token->tokenId = TokenId::UIntLiteral;
					token->exData = std::unique_ptr<TokenExtension, peff::DeallocableDeleter<TokenExtension>>(
						peff::allocAndConstruct<UIntTokenExtension>(allocator, sizeof(std::max_align_t), allocator, strtoul(prevYYCURSOR, nullptr, 2)));
					break;
				}

				<InitialCondition>[0-9]+"."[0-9]+[fF] {
					token->tokenId = TokenId::F32Literal;
					token->exData = std::unique_ptr<TokenExtension, peff::DeallocableDeleter<TokenExtension>>(
						peff::allocAndConstruct<F32TokenExtension>(allocator, sizeof(std::max_align_t), allocator, strtof(prevYYCURSOR, nullptr)));
					break;
				}

				<InitialCondition>[0-9]+"."[0-9]+ {
					token->tokenId = TokenId::F64Literal;
					token->exData = std::unique_ptr<TokenExtension, peff::DeallocableDeleter<TokenExtension>>(
						peff::allocAndConstruct<F64TokenExtension>(allocator, sizeof(std::max_align_t), allocator, strtod(prevYYCURSOR, nullptr)));
					break;
				}

				<InitialCondition>"\""		{ YYSETCONDITION(StringCondition); continue; }

				<InitialCondition>"\n"		{ token->tokenId = TokenId::NewLine; break; }
				<InitialCondition>"\000"	{ goto end; }

				<InitialCondition>[ \r\t]+	{ token->tokenId = TokenId::Whitespace; break; }

				<InitialCondition>[^]		{
					size_t beginIndex = prevYYCURSOR - src.data(), endIndex = YYCURSOR - src.data();
					std::string_view strToBegin = src.substr(0, beginIndex), strToEnd = src.substr(0, endIndex);

					size_t prevYYCURSORIndex = prevYYCURSOR - src.data();
					auto prevYYCURSORPos = src.find_last_of('\n', prevYYCURSORIndex);
					if(prevYYCURSORPos == std::string::npos)
						prevYYCURSORPos = 0;
					prevYYCURSORPos = prevYYCURSORIndex - prevYYCURSORPos;

					size_t YYCURSORIndex = YYCURSOR - src.data();
					auto YYCURSORPos = src.find_last_of('\n', YYCURSORIndex);
					if(YYCURSORPos == std::string::npos)
						YYCURSORPos = 0;
					YYCURSORPos = YYCURSORIndex - YYCURSORPos;

					return LexicalError {
						SourceLocation {
						{ (size_t)std::count(strToBegin.begin(), strToBegin.end(), '\n'), prevYYCURSORPos },
						{ (size_t)std::count(strToEnd.begin(), strToEnd.end(), '\n'), YYCURSORPos }
					}, "Invalid token"};
				}

				<StringCondition>"\""		{
					YYSETCONDITION(InitialCondition);
					token->tokenId = TokenId::StringLiteral;
					token->exData = std::unique_ptr<TokenExtension, peff::DeallocableDeleter<TokenExtension>>(
						peff::allocAndConstruct<StringTokenExtension>(allocator, sizeof(std::max_align_t), allocator, std::move(strLiteral)));
					break;
				}
				<StringCondition>"\\\n"		{ continue; }
				<StringCondition>"\\"		{ YYSETCONDITION(EscapeCondition); continue; }
				<StringCondition>"\n"		{
					size_t beginIndex = prevYYCURSOR - src.data(), endIndex = YYCURSOR - src.data();
					std::string_view strToBegin = src.substr(0, beginIndex), strToEnd = src.substr(0, endIndex);

					size_t prevYYCURSORIndex = prevYYCURSOR - src.data();
					auto prevYYCURSORPos = src.find_last_of('\n', prevYYCURSORIndex);
					if(prevYYCURSORPos == std::string::npos)
						prevYYCURSORPos = 0;
					prevYYCURSORPos = prevYYCURSORIndex - prevYYCURSORPos;

					size_t YYCURSORIndex = YYCURSOR - src.data();
					auto YYCURSORPos = src.find_last_of('\n', YYCURSORIndex);
					if(YYCURSORPos == std::string::npos)
						YYCURSORPos = 0;
					YYCURSORPos = YYCURSORIndex - YYCURSORPos;

					return LexicalError {
						SourceLocation {
						{ (size_t)std::count(strToBegin.begin(), strToBegin.end(), '\n'), prevYYCURSORPos },
						{ (size_t)std::count(strToEnd.begin(), strToEnd.end(), '\n'), YYCURSORPos }
					}, "Unexpected end of line"};
				}
				<StringCondition>"\000"	{
					size_t beginIndex = prevYYCURSOR - src.data(), endIndex = YYCURSOR - src.data();
					std::string_view strToBegin = src.substr(0, beginIndex), strToEnd = src.substr(0, endIndex);

					size_t prevYYCURSORIndex = prevYYCURSOR - src.data();
					auto prevYYCURSORPos = src.find_last_of('\n', prevYYCURSORIndex);
					if(prevYYCURSORPos == std::string::npos)
						prevYYCURSORPos = 0;
					prevYYCURSORPos = prevYYCURSORIndex - prevYYCURSORPos;

					size_t YYCURSORIndex = YYCURSOR - src.data();
					auto YYCURSORPos = src.find_last_of('\n', YYCURSORIndex);
					if(YYCURSORPos == std::string::npos)
						YYCURSORPos = 0;
					YYCURSORPos = YYCURSORIndex - YYCURSORPos;

					return LexicalError {
						SourceLocation {
						{ (size_t)std::count(strToBegin.begin(), strToBegin.end(), '\n'), prevYYCURSORPos },
						{ (size_t)std::count(strToEnd.begin(), strToEnd.end(), '\n'), YYCURSORPos }
					}, "Prematured end of file"};
				}
				<StringCondition>[^]		{ if(!strLiteral.pushBack(+YYCURSOR[-1])) goto outOfMemory; continue; }

				<EscapeCondition>"\'"	{ YYSETCONDITION(StringCondition); if(!strLiteral.pushBack('\'')) goto outOfMemory; continue; }
				<EscapeCondition>"\""	{ YYSETCONDITION(StringCondition); if(!strLiteral.pushBack('"')) goto outOfMemory; continue; }
				<EscapeCondition>"\?"	{ YYSETCONDITION(StringCondition); if(!strLiteral.pushBack('?')) goto outOfMemory; continue; }
				<EscapeCondition>"\\"	{ YYSETCONDITION(StringCondition); if(!strLiteral.pushBack('\\')) goto outOfMemory; continue; }
				<EscapeCondition>"a"	{ YYSETCONDITION(StringCondition); if(!strLiteral.pushBack('\a')) goto outOfMemory; continue; }
				<EscapeCondition>"b"	{ YYSETCONDITION(StringCondition); if(!strLiteral.pushBack('\b')) goto outOfMemory; continue; }
				<EscapeCondition>"f"	{ YYSETCONDITION(StringCondition); if(!strLiteral.pushBack('\f')) goto outOfMemory; continue; }
				<EscapeCondition>"n"	{ YYSETCONDITION(StringCondition); if(!strLiteral.pushBack('\n')) goto outOfMemory; continue; }
				<EscapeCondition>"r"	{ YYSETCONDITION(StringCondition); if(!strLiteral.pushBack('\r')) goto outOfMemory; continue; }
				<EscapeCondition>"t"	{ YYSETCONDITION(StringCondition); if(!strLiteral.pushBack('\t')) goto outOfMemory; continue; }
				<EscapeCondition>"v"	{ YYSETCONDITION(StringCondition); if(!strLiteral.pushBack('\v')) goto outOfMemory; continue; }
				<EscapeCondition>[0-7]{1,3}	{
					YYSETCONDITION(StringCondition);

					size_t size = YYCURSOR - prevYYCURSOR;

					char c = 0;
					for(uint_fast8_t i = 0; i < size; ++i) {
						c *= 8;
						c += prevYYCURSOR[i] - '0';
					}

					if(!strLiteral.pushBack(+c))
						goto outOfMemory;
				}
				<EscapeCondition>[xX][0-9a-fA-F]{1,2}	{
					YYSETCONDITION(StringCondition);

					size_t size = YYCURSOR - prevYYCURSOR;

					char c = 0, j;

					for(uint_fast8_t i = 1; i < size; ++i) {
						c *= 16;

						j = prevYYCURSOR[i];
						if((j >= '0') && (j <= '9'))
							c += prevYYCURSOR[i] - '0';
						else if((j >= 'a') && (j <= 'f'))
							c += prevYYCURSOR[i] - 'a';
						else if((j >= 'A') && (j <= 'F'))
							c += prevYYCURSOR[i] - 'A';
					}

					if(!strLiteral.pushBack(+c))
						goto outOfMemory;
				}

				<CommentCondition>"*"[/]	{ YYSETCONDITION(InitialCondition); break; }
				<CommentCondition>[^]		{ continue; }

				<LineCommentCondition>"\n"	{ YYSETCONDITION(InitialCondition); break; }
				<LineCommentCondition>[^]	{ continue; }
			*/
		}

		size_t beginIndex = prevYYCURSOR - src.data(), endIndex = YYCURSOR - src.data();

		std::string_view strToBegin = src.substr(0, beginIndex), strToEnd = src.substr(0, endIndex);

		token->sourceText = std::string_view(prevYYCURSOR, YYCURSOR - prevYYCURSOR);

		size_t idxLastBeginNewline = src.find_last_of('\n', beginIndex),
			   idxLastEndNewline = src.find_last_of('\n', endIndex);

		token->sourceLocation.beginPosition = {
			(size_t)std::count(strToBegin.begin(), strToBegin.end(), '\n'),
			(idxLastBeginNewline == std::string::npos
					? beginIndex
					: beginIndex - idxLastBeginNewline - 1)
		};
		token->sourceLocation.endPosition = {
			(size_t)std::count(strToEnd.begin(), strToEnd.end(), '\n'),
			(idxLastEndNewline == std::string::npos
					? endIndex
					: endIndex - idxLastEndNewline)
		};
		if (!tokenList.pushBack(std::move(token)))
			goto outOfMemory;

		prevYYCURSOR = YYCURSOR;
	}

end : {
	SourceLocation endLocation = token->sourceLocation;

	token = OwnedTokenPtr(peff::allocAndConstruct<Token>(allocator, sizeof(std::max_align_t), allocator));
	token->sourceLocation = endLocation;

	if (!tokenList.pushBack(std::move(token)))
		goto outOfMemory;
}

	return {};

outOfMemory:
	return LexicalError{ SourceLocation{ { 0, 0 }, { 0, 0 } }, "Out of memory" };
}
