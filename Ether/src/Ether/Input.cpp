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
#ifdef ETH_PLATFORM_WINDOWS
		s_Instance = new WindowsInput();
#endif
	}
}