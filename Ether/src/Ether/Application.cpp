#include "Application.h"
#include "Log.h"
#include <iostream>

#include "Ether/Events/Event.h"

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
		while(true);
	}
}