#include "etherpch.h"
#include "Application.h"
#include "Log.h"

#include "Ether/Events/Event.h"
#include "Ether/Events/KeyEvent.h"

namespace Ether
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		ETHER_CORE_INFO("Welcome to the Ehter engine.");
		ETHER_TRACE("Welcome to App.");

		KeyPressedEvent e(1, 100);
		if (e.IsInCategory(EventCategoryInput))
		{
			ETHER_TRACE(e);
		}
		while(true);
	}
}