#ifndef _CILVER_BASEDEFS_H_
#define _CILVER_BASEDEFS_H_

#include <trotvm/basedefs.h>

#if IS_TROTVM_BUILDING_
	#define KAST_API TROTVM_DLLEXPORT
#else
	#define KAST_API TROTVM_DLLIMPORT
#endif

#endif
