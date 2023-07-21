#pragma once

#include "Ether.h"

#include "Image.h"

namespace Ether
{
	class RayTracerLayer : public Layer
	{
	public:
		RayTracerLayer(const std::string& name);

		virtual ~RayTracerLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep ts) override;
		//以后也可能继续添加别的框架的东西
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;
	private:
		OrthographicCameraController m_OrthographicCameraController;
		Ref<Texture2D> m_BackgroundTexture;
		Ref<Image> m_Image;
		Ref<Framebuffer> m_Framebuffer;
		bool m_ViewportFocused = false, m_ViewportHovered = false;
	};
}