#include "etherpch.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace Ether
{
	static const uint32_t s_MaxFramebufferSize = 8192;

	namespace Utils
	{
		static GLenum TextureTarget(bool multisampled)
		{
			return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

		static bool IsDepthFormat(FramebufferTextureFormat format)
		{
			switch (format)
			{
				case FramebufferTextureFormat::DEPTH24STENCIL8:  return true;
			}

			return false;
		}

		static void CreateTexture(bool multisampled, uint32_t* outID, uint32_t count)
		{
			glCreateTextures(TextureTarget(multisampled), count, outID);
		}

		static void BindTexture(bool multisampled, uint32_t texture)
		{
			glBindTexture(TextureTarget(multisampled), texture);
		}

		static void AttachColorTexture(uint32_t texture, int samples,GLenum internal_format, GLenum format, uint32_t width, uint32_t height, int index)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), texture, 0);
		}

		static void AttachDepthTexture(uint32_t texture, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else
			{
				glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), texture, 0);
		}

		static GLenum InternalTextureFormatToGL(FramebufferTextureFormat format)
		{
			switch (format)
			{
				case FramebufferTextureFormat::RGBA8:
					return GL_RGBA8;
				case FramebufferTextureFormat::RED_INTEGER:
					return GL_RED_INTEGER;
			}

			ETHER_CORE_ASSERT(false, "UnKnown FramebufferTextureFormat.");
			return 0;
		}
	}

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
		: m_Spec(spec)
	{

		for (auto texture_spec : m_Spec.Attachments.Attachments)
		{
			if (!Utils::IsDepthFormat(texture_spec.TextureFormat))
			{
				m_ColorAttachmentSpecifications.emplace_back(texture_spec);
			}
			else
			{
				m_DepthAttachmentSpecification = texture_spec;
			}

		}

		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void OpenGLFramebuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Spec.Width, m_Spec.Height);
	}

	void OpenGLFramebuffer::UnBind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize)
		{
			ETHER_CORE_WARN("Attempted to rezize framebuffer to {0}, {1}", width, height);
			return;
		}

		m_Spec.Width = width;
		m_Spec.Height = height;

		Invalidate();
	}

	int OpenGLFramebuffer::ReadPixel(uint32_t attachment_index, int x, int y)
	{
		ETHER_CORE_ASSERT(attachment_index < m_ColorAttachments.size(), "attchment_index cross the bound.");

		//TOKNOW: 不用bind和unbind吗？
		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachment_index);
		int pixel_data = -1;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixel_data);
		return pixel_data;
	}

	void OpenGLFramebuffer::ClearAttachment(uint32_t attachment_index, int value)
	{
		ETHER_CORE_ASSERT(attachment_index < m_ColorAttachments.size(), "attchment_index cross the bound.");

		auto spec = m_ColorAttachmentSpecifications[attachment_index];
		glClearTexImage(m_ColorAttachments[attachment_index],
			0,
			Utils::InternalTextureFormatToGL(spec.TextureFormat),
			GL_INT,
			&value);
	}

	uint32_t OpenGLFramebuffer::GetColorAttachment(uint32_t index) const
	{
		ETHER_CORE_ASSERT(m_ColorAttachmentSpecifications.size() > index, "Index could not be larger than m_ColorAttachmentSpecifications.size()");
		return m_ColorAttachments[index];
	}

	const FramebufferSpecification& OpenGLFramebuffer::GetFramebufferSpecification() const
	{
		return m_Spec;
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (m_RendererID)
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
			glDeleteTextures(1, &m_DepthAttachment);

			m_ColorAttachments.clear();
			m_DepthAttachment = 0;
		}

		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		bool multisample = m_Spec.Samples > 1;
		//Attachmenst
		if (m_ColorAttachmentSpecifications.size())
		{
			m_ColorAttachments.resize(m_ColorAttachmentSpecifications.size());
			//批量创建GL_TEXTURE_2D或者GL_TEXTURE_2D_MULTISAMPLE
			Utils::CreateTexture(multisample, m_ColorAttachments.data(), m_ColorAttachments.size());

			for (uint32_t i = 0; i < m_ColorAttachments.size(); i++)
			{
				Utils::BindTexture(multisample, m_ColorAttachments[i]);
				switch (m_ColorAttachmentSpecifications[i].TextureFormat)
				{
					case FramebufferTextureFormat::RGBA8:
					{
						Utils::AttachColorTexture(m_ColorAttachments[i], m_Spec.Samples, GL_RGBA8, GL_RGBA, m_Spec.Width, m_Spec.Height, i);
						break;
					}
					case FramebufferTextureFormat::RED_INTEGER:
					{
						Utils::AttachColorTexture(m_ColorAttachments[i], m_Spec.Samples, GL_R32I, GL_RED_INTEGER, m_Spec.Width, m_Spec.Height, i);
						break;
					}
				}
			}
		}

		if (m_DepthAttachmentSpecification.TextureFormat != FramebufferTextureFormat::None)
		{
			Utils::CreateTexture(multisample, &m_DepthAttachment, 1);
			Utils::BindTexture(multisample, m_DepthAttachment);
			switch (m_DepthAttachmentSpecification.TextureFormat)
			{
				case FramebufferTextureFormat::DEPTH24STENCIL8:
				{
					Utils::AttachDepthTexture(m_DepthAttachment, m_Spec.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Spec.Width, m_Spec.Height);
					break;
				}
			}
		}

		//TODO: optimize these codes.
		if (m_ColorAttachments.size() > 1)
		{
			ETHER_CORE_ASSERT(m_ColorAttachments.size() <= 4, "m_ColorAttachments.size() > 4");
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(m_ColorAttachments.size(), buffers);
		}
		else if (m_ColorAttachments.empty())
		{
			// Only depth-pass
			glDrawBuffer(GL_NONE);
		}

		//glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		//glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Spec.Width, m_Spec.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		//glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
		//glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
		//glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Spec.Width, m_Spec.Height);
		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

		auto complete = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		ETHER_CORE_ASSERT(complete == GL_FRAMEBUFFER_COMPLETE, "OpenGL framebuffer is incomplete.");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}