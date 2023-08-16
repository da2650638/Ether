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

	void SceneCamera::OnEvent(Event& e)
	{
		ETHER_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<MouseScrolledEvent>( ETHER_BIND_EVENT_FN(OnMouseScrolled) );
	}

	bool SceneCamera::OnMouseScrolled(MouseScrolledEvent& e)
	{
		ETHER_PROFILE_FUNCTION();

		float orthographic_size = m_OrthographicSize;
		orthographic_size -= 0.25f * e.GetYOffset();
		orthographic_size = std::max((float)0.25, orthographic_size);
		SetOrthographicSize(orthographic_size);
		return false;
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

