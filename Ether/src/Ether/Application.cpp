#include "etherpch.h"
#include "Application.h"
#include "Log.h"

#include "Ether/Events/Event.h"
#include "Ether/Events/KeyEvent.h"
#include "Ether/Events/ApplicationEvent.h"

namespace Ether
{
	Application::Application()
		: m_Running(true),
		  m_LayerStack()
	{
		WindowProps props;
		m_Window.reset(Window::Create(props));
		m_Window->SetEventCallback( std::bind(&Application::OnEvent, this, std::placeholders::_1) );
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
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}
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