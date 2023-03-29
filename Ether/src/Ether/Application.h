#pragma once

#include "Ether/Core.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Ether
{
	class ETHER_API Application
	{
	public:
		Application();
		~Application();

		void InitImGui(GLFWwindow* window);
		void CreateNewFrameImGui();
		void RenderImGui();
		void CleanUpImGui();

		void Run();
	};

	Application* CreateApplication();
}