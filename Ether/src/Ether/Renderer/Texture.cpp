#include "etherpch.h"

#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Ether
{
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