#pragma once

#include "Ether/Renderer/Framebuffer.h"

namespace Ether
{
	class ETHER_API OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual void Resize(uint32_t width, uint32_t height) override;
		//virtual uint32_t GetColorAttachment() const override;
		virtual int ReadPixel(uint32_t attchment_index, int x, int y) override;

		virtual void ClearAttachment(uint32_t attachment_index, int value) override;

		virtual uint32_t GetColorAttachment(uint32_t index = 0) const override;
		virtual const FramebufferSpecification& GetFramebufferSpecification() const override;

	private:
		void Invalidate();
		FramebufferSpecification m_Spec;
		uint32_t m_RendererID = 0;

		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		FramebufferTextureSpecification m_DepthAttachmentSpecification = { FramebufferTextureFormat::None };

		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
	};
}
