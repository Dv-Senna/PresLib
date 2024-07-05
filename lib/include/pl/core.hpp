#pragma once


#ifdef PL_CORE
	#undef PL_CORE
#endif


#ifdef PL_STATIC
	#define PL_CORE
#else
	#ifdef PL_WINDOWS
		#ifdef PL_BUILD_LIB
			#define PL_CORE __declspec(dllexport)
		#else
			#define PL_CORE __declspec(dllimport)
		#endif
	#else
		#define PL_CORE
	#endif
#endif
