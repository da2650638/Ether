#pragma once

#include "RendererAPI.h"


namespace Ether
{
	class RenderCommand
	{
	public:
		RenderCommand() = default;
		~RenderCommand() = default;

		static void Init();
		static void SetClearColor(const glm::vec4& color);
		static void Clear();

		static void DrawIndexed(const Ref<VertexArray>& vertex_array);
	private:
		static RendererAPI *s_RendererAPI;
	};
}