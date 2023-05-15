#pragma once
#include "Ether/Core.h"
#include "Ether/Core/Timestep.h"
#include "Ether/Events/Event.h"
#include "Ether/Events/MouseEvent.h"
#include "Ether/Events/ApplicationEvent.h"
#include "Ether/Renderer/OrthographicCamera.h"

namespace Ether
{
	class ETHER_API OrthographicCameraController
	{
	public:
		OrthographicCameraController() = default;
		OrthographicCameraController(float aspect_ratio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;

		bool m_Rotation;

		OrthographicCamera m_Camera;

		glm::vec3 m_CameraPosition{ 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 0.15f;
		float m_CameraRotationSpeed = 9.0f;
	};
}