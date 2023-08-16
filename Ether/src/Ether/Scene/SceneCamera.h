#pragma once

#include "Ether/Events/MouseEvent.h"
#include "Ether/Renderer/Camera.h"

namespace Ether
{
	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetOrthographic(float size, float near_clip, float far_clip);

		void SetViewportSize(uint32_t width, uint32_t height);
		
		const float& GetOrthographicSize() const { return m_OrthographicSize; }
		void SetOrthographicSize(const float& orthographic_size) { m_OrthographicSize = orthographic_size; RecalculateProjection(); }

		void OnEvent(Event& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
	private:
		void RecalculateProjection();
	private:
		float m_OrthographicSize = 10.0f;
		float m_OrthographicNear = -1.0f;
		float m_OrthographicFar = 1.0f;

		float m_AspectRatio = 0.0f;
	};
}