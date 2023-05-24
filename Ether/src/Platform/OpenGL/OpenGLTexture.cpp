#include "etherpch.h"
#include "OpenGLTexture.h"

#include <stb_image.h>

namespace Ether
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_Width(width),
		  m_Height(height)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& img_path)
	{
		int width, height, channels;
		//翻转图片的y坐标使之与纹理的y坐标对应上
		stbi_set_flip_vertically_on_load(1);
		//加载图片到内存中来
		stbi_uc* data = stbi_load(img_path.c_str(), &width, &height, &channels, 0);
		ETHER_CORE_ASSERT(data, "Failed to load image {0}", img_path);
		m_Width = width;
		m_Height = height;

		GLenum internalFormat, format;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			format = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			format = GL_RGB;
		}

		//创建纹理对象
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		//设置纹理对象内部格式
		glTextureStorage2D(m_RendererID, 1, internalFormat, width, height);
		//设置纹理过滤方式
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//给纹理对象传入图像数据
		glTextureSubImage2D(m_RendererID, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);
		//将图片数据传入到GPU之后清理内存数据
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	uint32_t Ether::OpenGLTexture2D::GetWidth() const
	{
		return m_Width;
	}

	uint32_t OpenGLTexture2D::GetHeight() const
	{
		return m_Height;
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

	void OpenGLTexture2D::UnBind(uint32_t slot) const
	{
		glBindTextureUnit(slot, 0);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size) const
	{
		uint32_t bytes_per_pixel = m_DataFormat == GL_RGBA ? 4 : 3;
		ETHER_CORE_ASSERT(size == (m_Width * m_Height * bytes_per_pixel), "Data must be entire texture.");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}
}