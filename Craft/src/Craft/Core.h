#pragma once

#ifdef CRAFT_PLATFORM_WINDOWS
	#ifdef CRAFT_DYNAMIC_LINK
		#ifdef CRAFT_BUILD_DLL
			#define CRAFT_API __declspec(dllexport)
		#else		
			#define CRAFT_API __declspec(dllimport)
		#endif
	#else
		#define CRAFT_API
	#endif
#else
	#error Craft one support Windows
#endif

#ifdef CR_DEBUG
	#define CR_ASSERT(x, ...) { if (!(x)) { CR_ERROR(__VA_ARGS__); __debugbreak(); } }
#else
	#define CR_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)