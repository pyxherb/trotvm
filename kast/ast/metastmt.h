#ifndef _KAST_AST_METASTMT_H_
#define _KAST_AST_METASTMT_H_

#include "astnode.h"

namespace kast {
	enum class MetaStmtType : uint8_t {
		Expr = 0,	// Expression
		VarDef,		// (Local) Variable definition
		Break,		// Break
		Continue,	// Continue
		For,		// For
		While,		// While
		Return,		// Return
		If,			// If
		Switch,		// Switch
		CodeBlock,	// Code block

		Bad,  // Bad statement - unrecognized statement type
	};
}

#endif
