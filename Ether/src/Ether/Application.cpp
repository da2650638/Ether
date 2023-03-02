#include "Application.h"
#include "Log.h"
#include <iostream>

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
		ETHER_CORE_CRITICAL("Welcome to the Ehter engine.");
		ETHER_TRACE("Welcome to App.");
		while(true);
	}
}