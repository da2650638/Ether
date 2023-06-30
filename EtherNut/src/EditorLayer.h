#pragma once
#include "Ether.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Ether {

	class EditorLayer : public Layer {
	public:
		EditorLayer(const std::string& debugName);

		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Timestep ts) override;
		//以后也可能继续添加别的框架的东西
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;
	private:
		OrthographicCameraController m_OrthographicCameraController;
		Ref<Texture2D> m_Texture1, m_Texture2;
		Ref<Framebuffer> m_Framebuffer;
		float m_BgTilingFactor;
		float m_BgRotation;
		glm::vec4 m_BgTintColor;
		bool m_ViewportFocused = false, m_ViewportHovered = false;
	};

}