#pragma once

#include "etherpch.h"

#ifdef _WIN32
	#ifdef _WIN64
		#define ETH_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported."
	#endif
#elif
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	* so we must check all of them (in this order)
	* to ensure that we're running on MAC
	* and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define ETHER_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define ETHER_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
#endif

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

//using std::bind in modern C++ is a bad practice, as lambdas can do the same and much more
//#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define ETHER_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#ifdef ETH_DEBUG
    #define ETH_ENABLE_ASSERT
#endif


//TODO: Allow assert macro to take no arguments 
#ifdef ETH_ENABLE_ASSERT
#define ETHER_CORE_ASSERT(x, ...) { if(!(x)) { ETHER_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define ETHER_ASSERT(x, ...) { if(!(x)) { ETHER_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define ETHER_CORE_ASSERT(x, ...)
#define ETHER_ASSERT(x, ...)
#endif

namespace Ether {
	template <typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T>
	using Scope = std::unique_ptr<T>;
}