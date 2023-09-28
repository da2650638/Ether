#pragma once

#include "Ether/Renderer/Camera.h"
#include "Ether/Core/Timestep.h"
#include "Ether/Events/Event.h"
#include "Ether/Events/MouseEvent.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Ether
{
	class EditorCamera : public Camera
	{
	public:
		EditorCamera() = default;
		EditorCamera(float fov, float aspect_ratio, float near_clip, float far_clip);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		inline float GetDistance() const { return m_Distance; }
		inline void SetDistance(float distance) { m_Distance = distance; }

		inline void SetViewportSize(float width, float height)
		{
			m_ViewportWidth = width;
			m_ViewportHeight = height;
			UpdateProjection();
		}

		const glm::mat4& GetViewMatrix() const
		{
			return m_ViewMatrix;
		}

		glm::mat4 GetViewProjection() const
		{
			return m_Projection * m_ViewMatrix;
		}

		glm::vec3 GetUpDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetForwardDirection() const;
		const glm::vec3& GetPosition() const { return m_Position; }

		glm::quat GetOrientation() const;

		float GetPitch() const { return m_Pitch; }
		float GetYaw() const { return m_Yaw; }
	private:
		void UpdateProjection();
		void UpdateView();

		bool OnMouseScrolled(MouseScrolledEvent& e);

		//鼠标平移
		void MousePan(const glm::vec2& delta);
		//鼠标旋转
		void MouseRotate(const glm::vec2& delta);
		//鼠标缩放
		void MouseZoom(float delta);

		glm::vec3 CalculatePosition() const;

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;

	private:
		float m_FOV = 45.0f, m_AspectRatio = 1.778f, m_NearClip = 0.1f, m_FarClip = 1000.0f;

		glm::mat4 m_ViewMatrix;
		glm::vec3 m_Position = { 0.f, 0.f, 0.f };
		glm::vec3 m_FocalPoint = { 0.f, 0.f, 0.f };

		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };

		float m_Distance = 10.f;
		float m_Pitch = 0.0f/* 绕x轴旋转，上下晃动 */, m_Yaw = 0.0f /* 绕y轴旋转，左右晃动 */;

		float m_ViewportWidth = 1280, m_ViewportHeight = 720;
		
		friend class EditorLayer;
	};
}