#pragma once

#include "Ether/Core/Base.h"

namespace Ether
{
	struct FramebufferSpecification
	{
		uint32_t Width;
		uint32_t Height;

		uint32_t Samples = 1;
		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual ~Framebuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual void Resize(uint32_t width, uint32_t height) = 0;
		virtual uint32_t GetColorAttachment() const = 0;
		virtual const FramebufferSpecification& GetFramebufferSpecification() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	};
}