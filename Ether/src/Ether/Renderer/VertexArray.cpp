#include "etherpch.h"

#include "Renderer.h"
#include "VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Ether
{
	Ref<VertexArray> Ether::VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OpenGL:
				return  std::make_shared<OpenGLVertexArray>();
		}
		ETHER_CORE_ASSERT(false, "Unknow API type.");
		return nullptr;
	}
}