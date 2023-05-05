#include "etherpch.h"
#include "OpenGLContext.h"
#include "Ether/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ether
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{

	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ETHER_CORE_ASSERT(status, "Failed to initialized Glad.");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}