#pragma once

#include "Ether/Core/Core.h"
#include "Ether/Renderer/Texture.h"

namespace Ether
{
	class ETHER_API OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& img_path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;
		virtual void Bind(uint32_t slot) const override;
	private:
		std::string m_Path;
		uint32_t m_RendererID;
		uint32_t m_Width, m_Height;
	};
}