#pragma once

#include "Ether/Core.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"'
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Ether/Window.h"
#include "Ether/LayerStack.h"

namespace Ether
{
	class ETHER_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		bool m_Running;

		Scope<Window> m_Window;
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}