#include "etherpch.h"

#include "Renderer.h"
#include "RenderCommand.h"
#include "RenderCommandQueue.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Ether
{
	//TODO: shoudle be set dynamicly
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

	void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		//ETHER_RENDER_4(x, y, width, height, { s_RendererAPI->SetViewport(x, y, width, height); });
		s_RendererAPI->SetViewport(x, y, width, height);
	}

	void RenderCommand::Init()
	{
		//ETHER_RENDER({ s_RendererAPI->Init(); });
		s_RendererAPI->Init();
	}

	void RenderCommand::SetClearColor(const glm::vec4& color)
	{
		s_RendererAPI->SetClearColor(color);
		//ETHER_RENDER_1(color, { s_RendererAPI->SetClearColor(color); } );
	}

	void RenderCommand::Clear()
	{
		s_RendererAPI->Clear();
		//ETHER_RENDER({ s_RendererAPI->Clear(); });
	}

	void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertex_array)
	{
		//ETHER_RENDER_1(vertex_array, { s_RendererAPI->DrawIndexed(vertex_array); });
		s_RendererAPI->DrawIndexed(vertex_array);
	}
}