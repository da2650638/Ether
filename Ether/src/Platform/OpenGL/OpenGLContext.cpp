#include "etherpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Ether
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		Init();
	}

	void OpenGLContext::Init()
	{
		ETHER_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ETHER_CORE_ASSERT(status, "Failed to initialized Glad.");

		ETHER_CORE_INFO("OpenGL Info:");
		std::string vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
		std::string renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
		std::string version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
		ETHER_CORE_INFO(" Vendor:   {0}", vendor);
		ETHER_CORE_INFO(" Renderer: {0}", renderer);
		ETHER_CORE_INFO(" Version:  {0}", version);
#ifdef ETH_ENABLE_ASSERT
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
		bool result = (versionMajor >= 4 && versionMinor >= 5);
		ETHER_CORE_ASSERT(result, "Ether requires at least OpenGL version 4.5!");
#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		ETHER_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}