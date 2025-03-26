#ifndef _CILVER_BASEDEFS_H_
#define _CILVER_BASEDEFS_H_

#include <trotir/basedefs.h>

#if XYLO_IS_BUILDING
	#define XYLO_API TROTIR_DLLEXPORT
#else
	#define XYLO_API TROTIR_DLLIMPORT
#endif

#define XYLO_FORCEINLINE TROTIR_FORCEINLINE

#endif
