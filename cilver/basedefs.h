#ifndef _CILVER_BASEDEFS_H_
#define _CILVER_BASEDEFS_H_

#include <trotir/basedefs.h>

#if IS_TROTIR_BUILDING_
	#define CILVER_API TROTIR_DLLEXPORT
#else
	#define CILVER_API TROTIR_DLLIMPORT
#endif

#endif
