#pragma once


#ifdef ETH_PLATFORM_WINDOWS
	#ifdef ETH_BUILD_DLL
		#define ETHER_API __declspec(dllexport)
	#else
		#define ETHER_API __declspec(dllimport)
	#endif
#else
	#error Ether only supports windows.
#endif