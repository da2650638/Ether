#pragma once

#include "Ether/Core/Base.h"

namespace Ether
{
	enum class FramebufferTextureFormat
	{
		None = 0,

		//Color
		RGBA8,
		RED_INTEGER,

		//Depth/Stencil
		DEPTH24STENCIL8,

		//Defaults
		Depth = DEPTH24STENCIL8
	};

	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format)
			: TextureFormat(format) {}
		
		FramebufferTextureFormat TextureFormat;
		//TODO: filtering/Wrap
	};

	struct FramebufferAttachmentSpecification
	{
		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
			: Attachments(attachments) {}

		std::vector<FramebufferTextureSpecification> Attachments;
	};

	struct FramebufferSpecification
	{
		uint32_t Width;
		uint32_t Height;

		FramebufferAttachmentSpecification Attachments;

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
		//virtual uint32_t GetColorAttachment() const = 0;
		virtual int ReadPixel(uint32_t attchment_index, int x, int y) = 0;
		
		virtual void ClearAttachment(uint32_t attachment_index, int value) = 0;
		
		virtual uint32_t GetColorAttachment(uint32_t index = 0) const = 0;
		virtual const FramebufferSpecification& GetFramebufferSpecification() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	};
}