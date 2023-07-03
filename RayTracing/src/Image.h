#pragma once

#include "Ether.h"

namespace Ether
{
	class Image
	{
	public:
		Image();
		Image(uint32_t width, uint32_t height);
		~Image() { if (m_Image) delete m_Image; }

		void Init();
		uint32_t* GetPixels() { return m_Image; }
		const uint32_t& GetWidth() const { return m_ImageWidth; }
		const uint32_t& GetHeight() const { return m_ImageHeight; }
		const uint32_t& GetTextureRendererID() const { return m_Texture->GetRendererID(); }
		void OnResize(uint32_t width, uint32_t height);

		static Ref<Image> Create(uint32_t width, uint32_t height);
	private:
		uint32_t  m_ImageWidth;
		uint32_t  m_ImageHeight;
		uint32_t* m_Image;
		Ref<Texture> m_Texture;
	};

}