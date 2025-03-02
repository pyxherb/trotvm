#ifndef _XYLO_AST_METASTMT_H_
#define _XYLO_AST_METASTMT_H_

#include "astnode.h"

namespace xylo {
	enum class MetaStmtType : uint8_t {
		Expr = 0,	// Expression
		VarDef,		// (Local) Variable definition
		Break,		// Break
		Continue,	// Continue
		For,		// For
		Foreach,	// For each
		While,		// While
		Return,		// Return
		If,			// If
		Switch,		// Switch
		CodeBlock,	// Code block

		Bad,  // Bad statement - unrecognized statement type
	};
}

#endif
