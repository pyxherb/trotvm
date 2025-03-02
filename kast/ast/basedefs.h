#ifndef _CILVER_BASEDEFS_H_
#define _CILVER_BASEDEFS_H_

#include <trotvm/basedefs.h>

#if IS_KAST_BUILDING_
	#define KAST_API TROTVM_DLLEXPORT
#else
	#define KAST_API TROTVM_DLLIMPORT
#endif

#define KAST_FORCEINLINE TROTVM_FORCEINLINE

#endif
