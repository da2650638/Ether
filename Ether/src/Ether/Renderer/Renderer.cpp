#include "etherpch.h"

#include "Renderer.h"

namespace Ether
{
	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::SetClearColor(const glm::vec4& color)
	{
		RenderCommand::SetClearColor(color);
	}

	void Renderer::Clear()
	{
		RenderCommand::Clear();
	}
}