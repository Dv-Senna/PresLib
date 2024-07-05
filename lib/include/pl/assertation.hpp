#pragma once

#include <iostream>


#ifndef NDEBUG
	#define PL_ASSERT(cond, msg) if (!(cond)) {\
		std::cerr << "PL ASSERT FAILED : `" << #cond << "` > " << msg << std::endl;\
		__asm("int3");\
	}
#else
	#define PL_ASSERT(cond, msg)
#endif
