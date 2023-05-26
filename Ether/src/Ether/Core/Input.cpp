#include "etherpch.h"
#include "Input.h"

#ifdef ETH_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsInput.h"
#endif

namespace Ether
{
	Input* Input::s_Instance = nullptr;

	void Input::Create()
	{
		ETHER_PROFILE_FUNCTION();
#ifdef ETH_PLATFORM_WINDOWS
		s_Instance = new WindowsInput();
#endif
	}
	void Input::Destroy()
	{
		ETHER_PROFILE_FUNCTION();
#ifdef ETH_PLATFORM_WINDOWS
		if (s_Instance)
		{
			delete s_Instance;
		}
#endif
	}
}