#include "etherpch.h"

#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Ether
{
	//TODO: shoudle be set dynamicly
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

	void RenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		s_RendererAPI->SetViewport(x, y, width, height);
	}

	void RenderCommand::Init()
	{
		s_RendererAPI->Init();
	}

	void RenderCommand::SetClearColor(const glm::vec4& color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	void RenderCommand::Clear()
	{
		s_RendererAPI->Clear();
	}

	void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertex_array)
	{
		s_RendererAPI->DrawIndexed(vertex_array);
	}

	void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertex_array, uint32_t index_count)
	{
		s_RendererAPI->DrawIndexed(vertex_array, index_count);
	}
}