#pragma once

#include "Ether/Core/Base.h"
#include "Ether/Renderer/Texture.h"

#include <glad/glad.h>

namespace Ether
{
	class ETHER_API OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& img_path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;
		virtual void Bind(uint32_t slot) const override;
		virtual void UnBind(uint32_t slot) const override;
		virtual void SetData(void* data, uint32_t size) const override;
		virtual bool operator==(const Texture& other) const override;
	private:
		std::string m_Path;
		uint32_t m_RendererID;
		uint32_t m_Width, m_Height;
		GLenum m_InternalFormat, m_DataFormat;
	};
}