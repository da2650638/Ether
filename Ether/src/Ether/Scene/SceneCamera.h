#pragma once

#include "Ether/Events/MouseEvent.h"
#include "Ether/Renderer/Camera.h"

namespace Ether
{
	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetOrthographic(float size, float near_clip, float far_clip);
		void SetPerspective(float fov, float near_clip, float far_clip);

		void SetViewportSize(uint32_t width, uint32_t height);
		
		const float& GetOrthographicSize() const { return m_OrthographicSize; }
		void SetOrthographicSize(const float& orthographic_size) { m_OrthographicSize = orthographic_size; RecalculateProjection(); }

		const float& GetOrthographicNearClip() const { return m_OrthographicNear; }
		const float& GetOrthographicFarClip() const { return m_OrthographicFar; }

		void SetOrthographicNearClip(const float& orthographic_near) { m_OrthographicNear = orthographic_near; RecalculateProjection(); }
		void SetOrthographicFarClip(const float& orthographic_far) { m_OrthographicFar = orthographic_far; RecalculateProjection(); }

		const float& GetPerspectiveVerticalFOV() const { return m_PerspectiveVerticalFOV; }
		void SetPerspectiveVerticalFOV(const float& perspective_fov/* in radians */) { m_PerspectiveVerticalFOV = perspective_fov; RecalculateProjection(); }

		const float& GetPerspectiveNearClip() const { return m_PerpectiveNearClip; }
		void SetPerspectiveNearClip(const float& perspective_nearclip) { m_PerpectiveNearClip = perspective_nearclip; RecalculateProjection(); }

		const float& GetPerspectiveFarClip() const { return m_PerspectiveFarClip; }
		void SetPerspectiveFarClip(const float& perspective_farclip) { m_PerspectiveFarClip = perspective_farclip; RecalculateProjection(); }

	    const ProjectionType& GetProjectionType() const { return m_ProjectionType; }
		void SetProjectionType(const ProjectionType& projection_type) { m_ProjectionType = projection_type; RecalculateProjection(); }
	private:
		void RecalculateProjection();
	private:
		ProjectionType m_ProjectionType = ProjectionType::Orthographic;
		float m_OrthographicSize = 10.0f;
		float m_OrthographicNear = -1.0f;
		float m_OrthographicFar = 1.0f;

		float m_PerspectiveVerticalFOV = glm::radians(45.0f);
		float m_PerpectiveNearClip = 0.01f;
		float m_PerspectiveFarClip = 1000.0f;

		float m_AspectRatio = 0.0f;
	};
}