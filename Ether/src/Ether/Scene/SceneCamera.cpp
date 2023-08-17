#include "etherpch.h"
#include "SceneCamera.h"
#include "Ether/Core/Base.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Ether
{
	Ether::SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void Ether::SceneCamera::SetOrthographic(float size, float near_clip, float far_clip)
	{
		m_OrthographicSize = size;
		m_OrthographicNear = near_clip;
		m_OrthographicFar = far_clip;

		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;

		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		float ortho_left = -0.5 * m_AspectRatio * m_OrthographicSize;
		float ortho_right = 0.5 * m_AspectRatio * m_OrthographicSize;
		float ortho_bottom = -0.5 * m_OrthographicSize;
		float ortho_top = 0.5 * m_OrthographicSize;

		m_Projection = glm::ortho(ortho_left, ortho_right, ortho_bottom, ortho_top, m_OrthographicNear, m_OrthographicFar);
	}
}
