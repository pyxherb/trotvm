#ifndef _CILVER_BASEDEFS_H_
#define _CILVER_BASEDEFS_H_

#include <trotvm/basedefs.h>

#if XYLO_IS_BUILDING
	#define XYLO_API TROTVM_DLLEXPORT
#else
	#define XYLO_API TROTVM_DLLIMPORT
#endif

#define XYLO_FORCEINLINE TROTVM_FORCEINLINE

#endif
