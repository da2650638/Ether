#include "etherpch.h"
#include "Application.h"
#include "Log.h"

#include "Ether/Renderer/Renderer.h"
#include "Ether/Events/Event.h"
#include "Ether/Events/KeyEvent.h"
#include "Ether/Events/ApplicationEvent.h"
#include "Ether/Core/Input.h"
#include "Ether/Core/Timestep.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Ether
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
		: m_Running(true),
		  m_LayerStack(),
		  m_LastFrameTime(0.0f)
	{
		ETHER_PROFILE_FUNCTION();

		ETHER_CORE_ASSERT((s_Instance == nullptr), "Application instance already exist.");
		s_Instance = this;

		WindowProps props{"Ether Engine", 1280, 720};
		m_Window.reset(Window::Create(props));
		m_Window->SetEventCallback( std::bind(&Application::OnEvent, this, std::placeholders::_1) );
		m_Window->SetVSync(false);

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		ETHER_PROFILE_FUNCTION();
		Renderer::ShutDown();
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::Run()
	{
		ETHER_PROFILE_FUNCTION();

		ETHER_CORE_INFO("Welcome to the Ehter engine.");
		ETHER_TRACE("Welcome to App.");

		while (m_Running)
		{
			float now = glfwGetTime();
			Timestep ts(now - m_LastFrameTime);
			m_LastFrameTime = now;

			if (!m_Minimized)
			{
				{
					ETHER_PROFILE_SCOPE("LayerStack OnUpdate");
					for (Layer* layer : m_LayerStack)
					{
						layer->OnUpdate(ts);
					}
				}

				m_ImGuiLayer->Begin();
				{
					ETHER_PROFILE_SCOPE("LayerStack OnImGuiRender");
					for (Layer* layer : m_LayerStack)
					{
						layer->OnImGuiRender();
					}
				}
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		ETHER_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>( std::bind(&Application::OnWindowClose, this, std::placeholders::_1) );
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));
		
		//iterate the layer stack
		//TODO: OnEvent为什么从后往前呢？
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		ETHER_PROFILE_FUNCTION();
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		ETHER_PROFILE_FUNCTION();
		m_LayerStack.PushOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		ETHER_PROFILE_FUNCTION();
		ETHER_CORE_INFO("Closing Application...");
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		ETHER_PROFILE_FUNCTION();
		ETHER_CORE_INFO(e);
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}