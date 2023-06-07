#pragma once
#include "Ether/Core/Base.h"
#include "Ether/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Ether
{
	class ETHER_API OpenGLContext : public GraphicsContext 
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init();
		virtual void SwapBuffers();
	private:
		GLFWwindow* m_WindowHandle;
	};
}