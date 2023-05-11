#pragma once

#include "Ether/Core.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"'
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Ether/Window.h"
#include "Ether/LayerStack.h"
#include "Ether/ImGui/ImGuiLayer.h"

namespace Ether
{
	class ETHER_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		//在Window类及其子类当中通过SetEventCallback被设置到成员变量当中当作回调函数。
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		
		inline Window& GetWindow() { return *m_Window; }
		static inline Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		bool m_Running;

		Scope<Window> m_Window;
		LayerStack m_LayerStack;

		ImGuiLayer* m_ImGuiLayer;

		float m_LastFrameTime;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();
}