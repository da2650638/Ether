#include "etherpch.h"
#include "WindowsWindow.h"
#include "Ether/Log.h"
#include "Ether/Events/ApplicationEvent.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Ether {
	static bool s_GLFWInitialized = false;

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
		if (enabled)
		{
			glfwSwapInterval(1);
			return;
		}

		glfwSwapInterval(0);
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();

			ETHER_CORE_ASSERT(success, "Could not intialize GLFW! return value:{0}", success);

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		ETHER_CORE_ASSERT(m_Window, "GLFW Failed to create window.");

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent e;
			data->Callback(e);
        });

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			WindowResizeEvent e(width, height);
			data->Callback(e);
        });
	}

	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(m_Window);
	}
}