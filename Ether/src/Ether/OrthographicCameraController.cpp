#include "etherpch.h"

#include "OrthographicCameraController.h"
#include "Ether/Input.h"
#include "Ether/KeyCodes.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Ether
{
    OrthographicCameraController::OrthographicCameraController(float aspect_ratio, bool rotation)
        : m_AspectRatio(aspect_ratio),
        m_ZoomLevel(1.0f),
        m_Rotation(rotation),
        m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
    {
    }

    void OrthographicCameraController::OnUpdate(Timestep ts)
    {
        if (Input::IsKeyPressed(ETHER_KEY_W))
        {
            m_CameraPosition.y += ts * m_CameraTranslationSpeed;
        }
        if (Input::IsKeyPressed(ETHER_KEY_S))
        {
            m_CameraPosition.y -= ts * m_CameraTranslationSpeed;
        }
        if (Input::IsKeyPressed(ETHER_KEY_A))
        {
            m_CameraPosition.x -= ts * m_CameraTranslationSpeed;
        }
        if (Input::IsKeyPressed(ETHER_KEY_D))
        {
            m_CameraPosition.x += ts * m_CameraTranslationSpeed;
        }
        m_Camera.SetPosition(m_CameraPosition);

        if (m_Rotation)
        {
            if (Input::IsKeyPressed(ETHER_KEY_J))
            {
                m_CameraRotation += ts * m_CameraRotationSpeed;
            }
            if (Input::IsKeyPressed(ETHER_KEY_L))
            {
                m_CameraRotation -= ts * m_CameraRotationSpeed;
            }
            m_Camera.SetRotation(m_CameraRotation);
        }

        m_CameraTranslationSpeed = m_ZoomLevel;
    }

    void OrthographicCameraController::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&OrthographicCameraController::OnMouseScrolled, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&OrthographicCameraController::OnWindowResize, this, std::placeholders::_1));
    }

    bool OrthographicCameraController::OnWindowResize(WindowResizeEvent& e)
    {
        uint32_t width = e.GetWidth(), height = e.GetHeight();
        m_AspectRatio = (float)width / (float)height;
        m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
    {
        m_ZoomLevel += 0.25f * e.GetYOffset();
        m_ZoomLevel = std::max((float)0.25, m_ZoomLevel);
        m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
        return false;
    }
}