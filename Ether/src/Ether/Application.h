#pragma once

#include "Ether/Core.h"

namespace Ether
{
	class ETHER_API Application
	{
	public:
		Application();
		~Application();

		void Run();
	};

	Application* CreateApplication();
}