#pragma once

#include "RendererAPI.h"


namespace Ether
{
	class RenderCommand
	{
	public:
		RenderCommand() = default;
		~RenderCommand() = default;

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		static void Init();
		static void SetClearColor(const glm::vec4& color);
		static void Clear();

		static void DrawIndexed(const Ref<VertexArray>& vertex_array);
		static void DrawIndexed(const Ref<VertexArray>& vertex_array, uint32_t index_count);
	private:
		static RendererAPI *s_RendererAPI;
	};
}