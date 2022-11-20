

#include "Application.h"

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
		std::cout << "Welcome to Ether Engine." << std::endl;
		while(true);
	}
}