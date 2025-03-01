#ifndef _XYLO_AST_STMT_H_
#define _XYLO_AST_STMT_H_

#include "astnode.h"

namespace xylo {
	enum class StmtType : uint8_t {
		Expr = 0,	// Expression
		VarDef,		// (Local) Variable definition
		Break,		// Break
		Continue,	// Continue
		For,		// For
		While,		// While
		Return,		// Return=
		If,			// If
		Switch,		// Switch
		CodeBlock,	// Code block
		Goto,		// Goto

		Bad,  // Bad statement - unrecognized statement type
	};
}

#endif
