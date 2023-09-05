#include "etherpch.h"
#include "WindowsWindow.h"
#include "Ether/Core/Log.h"
#include "Ether/Events/ApplicationEvent.h"
#include "Ether/Events/MouseEvent.h"
#include "Ether/Events/KeyEvent.h"
#include "Ether/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Ether {
	static uint8_t s_GLFWWindowCount = 0;

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		ETHER_PROFILE_FUNCTION();

		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ETHER_PROFILE_FUNCTION();

		ShutDown();
	}

	void WindowsWindow::OnUpdate()
	{
		ETHER_PROFILE_FUNCTION();

		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		ETHER_PROFILE_FUNCTION();

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
		ETHER_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		if (s_GLFWWindowCount == 0)
		{
			int success = glfwInit();

			ETHER_CORE_ASSERT(success, "Could not intialize GLFW! return value:{0}", success);

			s_GLFWWindowCount++;
		}
#ifdef ETH_DEBUG
		if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		ETHER_CORE_ASSERT(m_Window, "GLFW Failed to create window.");

		m_Context = new OpenGLContext(m_Window);

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

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent e((float)xoffset, (float)yoffset);
			data->Callback(e);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_RELEASE:
			{
				KeyReleasedEvent e((KeyCode)key);
				data->Callback(e);
				break;
			}
			case GLFW_PRESS:
			{
				KeyPressedEvent e((KeyCode)key, 0);
				data->Callback(e);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent e((KeyCode)key, true);
				data->Callback(e);
				break;
			}
			}
		});
	}

	void WindowsWindow::ShutDown()
	{
		ETHER_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;
		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}
}