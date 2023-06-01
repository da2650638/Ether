#pragma once

#include "Ether/Core/Core.h"
#include "Ether/Events/Event.h"
#include "Ether/Events/KeyEvent.h"'
#include "Ether/Events/ApplicationEvent.h"
#include "Ether/Events/MouseEvent.h"
#include "Ether/Core/Window.h"
#include "Ether/Core/LayerStack.h"
#include "Ether/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Ether
{
	class ETHER_API Application
	{
	public:
		Application();
		virtual ~Application();

		//在Window类及其子类当中通过SetEventCallback被设置到成员变量当中当作回调函数。
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		
		inline Window& GetWindow() { return *m_Window; }
		static inline Application& Get() { return *s_Instance; }

	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		bool m_Running;
		bool m_Minimized = false;

		Scope<Window> m_Window;
		LayerStack m_LayerStack;

		ImGuiLayer* m_ImGuiLayer;

		float m_LastFrameTime;
	private:
		static Application* s_Instance;
		//在EntryPoint.h里边被实现
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}