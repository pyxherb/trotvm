#ifndef _TROTIR_BASEDEFS_H_
#define _TROTIR_BASEDEFS_H_

#include <peff/base/basedefs.h>

#if TROTIR_BUILD_SHARED
	#if defined(_MSC_VER)
		#define TROTIR_DLLEXPORT __declspec(dllexport)
		#define TROTIR_DLLIMPORT __declspec(dllimport)
	#elif defined(__GNUC__) || defined(__clang__)
		#define TROTIR_DLLEXPORT __attribute__((__visibility__("default")))
		#define TROTIR_DLLIMPORT __attribute__((__visibility__("default")))
	#endif
#else
	#define TROTIR_DLLEXPORT
	#define TROTIR_DLLIMPORT
#endif

#define TROTIR_FORCEINLINE PEFF_FORCEINLINE

#define TROTIR_DECL_EXPLICIT_INSTANTIATED_CLASS(apiModifier, name, ...) \
	PEFF_DECL_EXPLICIT_INSTANTIATED_CLASS(apiModifier, name, ##__VA_ARGS__)
#define TROTIR_DEF_EXPLICIT_INSTANTIATED_CLASS(apiModifier, name, ...) \
	PEFF_DEF_EXPLICIT_INSTANTIATED_CLASS(apiModifier, name, ##__VA_ARGS__)

#if TROTIR_IS_BUILDING
	#define TROTIR_API TROTIR_DLLEXPORT
#else
	#define TROTIR_API TROTIR_DLLIMPORT
#endif

#endif
