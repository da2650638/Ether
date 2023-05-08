#include "etherpch.h"

#include "Renderer.h"
#include "VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Ether
{
	VertexArray* Ether::VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::OpenGL:
				return new OpenGLVertexArray();
		}
		ETHER_CORE_ASSERT(false, "Unknow API type.");
		return nullptr;
	}
}