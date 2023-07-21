#include "Image.h"

namespace Ether
{
	Image::Image()
		: m_Image(nullptr)
	{

	}

	Image::Image(uint32_t width, uint32_t height)
		: m_Image(nullptr),
		  m_ImageWidth(width),
		  m_ImageHeight(height)
	{
		Init();
	}

	void Image::Init()
	{
		m_Image = new uint32_t[m_ImageWidth * m_ImageHeight];
		uint32_t pixel_color = 0xff000000;
		memset(m_Image, 0, m_ImageWidth * m_ImageHeight * sizeof(uint32_t));
		for (uint32_t y = 0; y < m_ImageHeight; y++)
		{
			for (uint32_t x = 0; x < m_ImageWidth; x++)
			{
				float rf = ((float)x / (float)m_ImageWidth) * 255.0f;
				float gf = ((float)y / (float)m_ImageHeight) * 255.0f;
				uint32_t rb = (uint32_t)rf, gb = (uint32_t)gf;
				pixel_color |= (gb << 8);
				pixel_color |= (rb);
				m_Image[m_ImageWidth * y + x] = pixel_color;
				pixel_color = 0xff000000;
			}
		}

		m_Texture = Texture2D::Create(m_ImageWidth, m_ImageHeight);
		m_Texture->SetData(m_Image, m_ImageWidth * m_ImageHeight * sizeof(uint32_t));
	}

	void Image::OnResize(uint32_t width, uint32_t height)
	{
		if (m_Image)
			delete m_Image;

		m_ImageWidth = width;
		m_ImageHeight = height;
		Init();
	}

	Ref<Image> Image::Create(uint32_t width, uint32_t height)
	{
		return std::make_shared<Image>(width, height);
	}
}