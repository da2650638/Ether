#pragma once

#include "etherpch.h"

#ifdef ETH_PLATFORM_WINDOWS
	#ifdef ETHER_DYNAMIC_LIB
		#ifdef ETH_BUILD_DLL
			#define ETHER_API __declspec(dllexport)
		#else
			#define ETHER_API __declspec(dllimport)
		#endif
	#else
		#define ETHER_API
	#endif
#else
	#error Ether only supports windows.
#endif

#define BIT(x) (1 << (x))

#ifdef ETH_DEBUG
    #define ETH_ENABLE_ASSERT
#endif

#ifdef ETH_ENABLE_ASSERT
#define ETHER_CORE_ASSERT(x, ...) { if(!x) { ETHER_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define ETHER_ASSERT(x, ...) { if(!x) { ETHER_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#elif
#define ETHER_CORE_ASSERT(x, ...)
#define ETHER_ASSERT(x, ...)
#endif

namespace Ether {
	template <typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T>
	using Scope = std::unique_ptr<T>;
}