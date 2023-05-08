#include "etherpch.h"
#include "Application.h"
#include "Log.h"

#include "Ether/Events/Event.h"
#include "Ether/Events/KeyEvent.h"
#include "Ether/Events/ApplicationEvent.h"
#include "Ether/Input.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Ether
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
		: m_Running(true),
		  m_LayerStack()
	{
		ETHER_CORE_ASSERT((s_Instance == nullptr), "Application instance already exist.");
		s_Instance = this;

		WindowProps props;
		m_Window.reset(Window::Create(props));
		m_Window->SetEventCallback( std::bind(&Application::OnEvent, this, std::placeholders::_1) );

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		Input::Create();

		//Vertex Array
		//Vertex Buffer
		//Index Buffer
		//Shader
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		ETHER_CORE_INFO("Welcome to the Ehter engine.");
		ETHER_TRACE("Welcome to App.");

		while (m_Running)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>( std::bind(&Application::OnWindowClose, this, std::placeholders::_1) );
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));
		
		//iterate the layer stack
		for (Layer* layer : m_LayerStack)
		{
			layer->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		ETHER_CORE_INFO("Closing Application...");
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		ETHER_CORE_INFO(e);
		return true;
	}
}