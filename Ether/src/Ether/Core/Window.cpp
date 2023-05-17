#include "etherpch.h"
#include "Window.h"

#ifdef ETH_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Ether {

	Window* Window::Create(const WindowProps & props)
	{
#ifdef ETH_PLATFORM_WINDOWS
		return  new WindowsWindow(props);
#elif ETH_PLATFORM_LINUX
		return  new WindowsWindow(props);
#endif
	}

}