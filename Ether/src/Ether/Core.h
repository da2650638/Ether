#pragma once

#include <memory>

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

namespace Ether {
	template <typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T>
	using Scope = std::unique_ptr<T>;
}