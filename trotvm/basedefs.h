#ifndef _TROTVM_BASEDEFS_H_
#define _TROTVM_BASEDEFS_H_

#include <peff/base/basedefs.h>

#if TROTVM_BUILD_SHARED
	#if defined(_MSC_VER)
		#define TROTVM_DLLEXPORT __declspec(dllexport)
		#define TROTVM_DLLIMPORT __declspec(dllimport)
	#elif defined(__GNUC__) || defined(__clang__)
		#define TROTVM_DLLEXPORT __attribute__((__visibility__("default")))
		#define TROTVM_DLLIMPORT __attribute__((__visibility__("default")))
	#endif
#else
	#define TROTVM_DLLEXPORT
	#define TROTVM_DLLIMPORT
#endif

#define TROTVM_FORCEINLINE PEFF_FORCEINLINE

#define TROTVM_DECL_EXPLICIT_INSTANTIATED_CLASS(apiModifier, name, ...) \
	PEFF_DECL_EXPLICIT_INSTANTIATED_CLASS(apiModifier, name, ##__VA_ARGS__)
#define TROTVM_DEF_EXPLICIT_INSTANTIATED_CLASS(apiModifier, name, ...) \
	PEFF_DEF_EXPLICIT_INSTANTIATED_CLASS(apiModifier, name, ##__VA_ARGS__)

#if IS_TROTVM_BUILDING_
	#define TROTVM_API TROTVM_DLLEXPORT
#else
	#define TROTVM_API TROTVM_DLLIMPORT
#endif

#endif
