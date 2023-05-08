#pragma once

#include "RendererAPI.h"

namespace Ether
{
	class Renderer
	{
	public:
		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}