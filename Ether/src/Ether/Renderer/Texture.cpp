#include "etherpch.h"

#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Ether
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
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
				return std::make_shared<OpenGLTexture2D>(width, height);
			}
		}

		ETHER_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const std::string img_path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLTexture2D>(img_path);
		}
		ETHER_CORE_ASSERT(false, "Unknow API type.");
		return nullptr;
	}
}