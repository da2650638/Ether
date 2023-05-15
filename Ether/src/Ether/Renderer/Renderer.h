#pragma once

#include "RendererAPI.h"
#include "RenderCommand.h"

namespace Ether
{
	class Renderer
	{
	public:
		static void Init();

		static void SetClearColor(const glm::vec4& color);
		static void Clear();

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}