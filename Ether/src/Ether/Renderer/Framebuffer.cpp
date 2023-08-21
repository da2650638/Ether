#include "etherpch.h"

#include "Ether/Renderer/Framebuffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Ether
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				ETHER_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return std::make_shared<OpenGLFramebuffer>(spec);
			}
		}

		ETHER_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}