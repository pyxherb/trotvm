#include "lexer.h"

using namespace xylo;

XYLO_API TokenExtension::~TokenExtension() {}

XYLO_API IntTokenExtension::IntTokenExtension(peff::Alloc *allocator, int data) : allocator(allocator), data(data) {
}
XYLO_API IntTokenExtension::~IntTokenExtension() {
}
XYLO_API void IntTokenExtension::dealloc() {
	peff::destroyAndRelease<IntTokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API UIntTokenExtension::UIntTokenExtension(peff::Alloc *allocator, unsigned int data) : allocator(allocator), data(data) {
}
XYLO_API UIntTokenExtension::~UIntTokenExtension() {
}
XYLO_API void UIntTokenExtension::dealloc() {
	peff::destroyAndRelease<UIntTokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API LongTokenExtension::LongTokenExtension(peff::Alloc *allocator, long long data) : allocator(allocator), data(data) {
}
XYLO_API LongTokenExtension::~LongTokenExtension() {
}
XYLO_API void LongTokenExtension::dealloc() {
	peff::destroyAndRelease<LongTokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API ULongTokenExtension::ULongTokenExtension(peff::Alloc *allocator, unsigned long long data) : allocator(allocator), data(data) {
}
XYLO_API ULongTokenExtension::~ULongTokenExtension() {
}
XYLO_API void ULongTokenExtension::dealloc() {
	peff::destroyAndRelease<ULongTokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API F32TokenExtension::F32TokenExtension(peff::Alloc *allocator, float data) : allocator(allocator), data(data) {
}
XYLO_API F32TokenExtension::~F32TokenExtension() {
}
XYLO_API void F32TokenExtension::dealloc() {
	peff::destroyAndRelease<F32TokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API F64TokenExtension::F64TokenExtension(peff::Alloc *allocator, double data) : allocator(allocator), data(data) {
}
XYLO_API F64TokenExtension::~F64TokenExtension() {
}
XYLO_API void F64TokenExtension::dealloc() {
	peff::destroyAndRelease<F64TokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API StringTokenExtension::StringTokenExtension(peff::Alloc *allocator, peff::String &&data) : allocator(allocator), data(std::move(data)) {
}
XYLO_API StringTokenExtension::~StringTokenExtension() {
}
XYLO_API void StringTokenExtension::dealloc() {
	peff::destroyAndRelease<StringTokenExtension>(allocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API Token::Token(peff::Alloc* allocator) : allocator(allocator) {
}
XYLO_API Token::~Token() {
}
XYLO_API void Token::dealloc() {
	peff::destroyAndRelease<Token>(allocator.get(), this, sizeof(std::max_align_t));
}

XYLO_API const char* getTokenName(TokenId tokenId) {
	switch (tokenId) {
		case TokenId::End:
			return "EOF";
		case TokenId::Id:
			return "identifier";
		case TokenId::Comma:
			return ",";
		case TokenId::Question:
			return "?";
		case TokenId::Colon:
			return ":";
		case TokenId::Semicolon:
			return ";";
		case TokenId::LBracket:
			return "[";
		case TokenId::RBracket:
			return "]";
		case TokenId::LBrace:
			return "{";
		case TokenId::RBrace:
			return "}";
		case TokenId::LParenthese:
			return "(";
		case TokenId::RParenthese:
			return ")";
		case TokenId::At:
			return "@";
		case TokenId::Dot:
			return ".";
		case TokenId::VarArg:
			return "...";
		case TokenId::ScopeOp:
			return "::";
		case TokenId::MatchOp:
			return "=>";
		case TokenId::LAndOp:
			return "&&";
		case TokenId::LOrOp:
			return "||";
		case TokenId::AddOp:
			return "+";
		case TokenId::SubOp:
			return "-";
		case TokenId::MulOp:
			return "*";
		case TokenId::DivOp:
			return "/";
		case TokenId::ModOp:
			return "%";
		case TokenId::AndOp:
			return "&";
		case TokenId::OrOp:
			return "|";
		case TokenId::XorOp:
			return "^";
		case TokenId::LNotOp:
			return "!";
		case TokenId::NotOp:
			return "~";
		case TokenId::AssignOp:
			return "=";
		case TokenId::AddAssignOp:
			return "+=";
		case TokenId::SubAssignOp:
			return "-=";
		case TokenId::MulAssignOp:
			return "*=";
		case TokenId::DivAssignOp:
			return "/=";
		case TokenId::ModAssignOp:
			return "%=";
		case TokenId::AndAssignOp:
			return "&";
		case TokenId::OrAssignOp:
			return "|";
		case TokenId::XorAssignOp:
			return "^";
		case TokenId::LshAssignOp:
			return "<<=";
		case TokenId::RshAssignOp:
			return ">>=";
		case TokenId::EqOp:
			return "==";
		case TokenId::NeqOp:
			return "!=";
		case TokenId::LshOp:
			return "<<";
		case TokenId::RshOp:
			return ">>";
		case TokenId::LtEqOp:
			return "<=";
		case TokenId::GtEqOp:
			return ">=";
		case TokenId::LtOp:
			return "<";
		case TokenId::GtOp:
			return ">";
		case TokenId::DollarOp:
			return "$";

		case TokenId::VoidTypeName:
			return "void";
		case TokenId::I8TypeName:
			return "i8";
		case TokenId::I16TypeName:
			return "i16";
		case TokenId::I32TypeName:
			return "i32";
		case TokenId::I64TypeName:
			return "i64";
		case TokenId::U8TypeName:
			return "u8";
		case TokenId::U16TypeName:
			return "u16";
		case TokenId::U32TypeName:
			return "u32";
		case TokenId::U64TypeName:
			return "u64";
		case TokenId::ISizeTypeName:
			return "isize";
		case TokenId::USizeTypeName:
			return "usize";
		case TokenId::F32TypeName:
			return "f32";
		case TokenId::F64TypeName:
			return "f64";
		case TokenId::BoolTypeName:
			return "bool";

		case TokenId::LetKeyword:
			return "let";
		case TokenId::AsKeyword:
			return "as";
		case TokenId::IfKeyword:
			return "if";
		case TokenId::ElseKeyword:
			return "else";
		case TokenId::SwitchKeyword:
			return "switch";
		case TokenId::CaseKeyword:
			return "case";
		case TokenId::ReturnKeyword:
			return "return";
		case TokenId::ForKeyword:
			return "for";
		case TokenId::WhileKeyword:
			return "while";
		case TokenId::DoKeyword:
			return "do";
		case TokenId::StructKeyword:
			return "struct";
		case TokenId::EnumKeyword:
			return "enum";
		case TokenId::FnKeyword:
			return "fn";
		case TokenId::TypenameKeyword:
			return "typename";
		case TokenId::DeferKeyword:
			return "defer";
		case TokenId::ImportKeyword:
			return "import";
		case TokenId::MacroKeyword:
			return "macro";
		case TokenId::ExternKeyword:
			return "extern";
		case TokenId::StaticKeyword:
			return "static";
		case TokenId::YieldKeyword:
			return "yield";
		case TokenId::AwaitKeyword:
			return "await";
		case TokenId::AsyncKeyword:
			return "async";
		case TokenId::ConstKeyword:
			return "const";
		case TokenId::UsingKeyword:
			return "using";
		case TokenId::AliasKeyword:
			return "alias";
		case TokenId::UnionKeyword:
			return "union";
		case TokenId::AttributeKeyword:
			return "attribute";
		case TokenId::ThisKeyword:
			return "this";
		case TokenId::SelfKeyword:
			return "self";
		case TokenId::ImplKeyword:
			return "impl";
		case TokenId::DefKeyword:
			return "def";
		case TokenId::GotoKeyword:
			return "goto";
		case TokenId::SizeofKeyword:
			return "sizeof";
		case TokenId::NamespaceKeyword:
			return "namespace";
		case TokenId::MutableKeyword:
			return "mutable";
		case TokenId::VolatileKeyword:
			return "volatile";

		case TokenId::IntLiteral:
			return "int literal";
		case TokenId::LongLiteral:
			return "long literal";
		case TokenId::UIntLiteral:
			return "unsigned int literal";
		case TokenId::ULongLiteral:
			return "unsigned long literal";
		case TokenId::F32Literal:
			return "f32 literal";
		case TokenId::F64Literal:
			return "f64 literal";
		case TokenId::StringLiteral:
			return "string literal";

		case TokenId::Whitespace:
			return "whitespace";
		case TokenId::NewLine:
			return "new line";
		case TokenId::LineComment:
			return "line comment";
		case TokenId::BlockComment:
			return "block comment";
		case TokenId::DocumentationComment:
			return "documentation comment";
		default:;
	}

	return "<unknown token>";
}
