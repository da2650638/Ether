#pragma once

#include "Ether/Renderer/RendererAPI.h"

namespace Ether
{
	class ETHER_API OpenGLRendererAPI : public RendererAPI
	{
	public:
		OpenGLRendererAPI();
		virtual ~OpenGLRendererAPI();

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertex_array) override;
	};
}