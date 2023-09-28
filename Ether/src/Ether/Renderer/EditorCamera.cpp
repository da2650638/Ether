#include "etherpch.h"
#include "EditorCamera.h"
#include "Ether/Core/Input.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Ether
{
    EditorCamera::EditorCamera(float fov, float aspect_ratio, float near_clip, float far_clip)
        : m_FOV(fov), m_AspectRatio(aspect_ratio), m_NearClip(near_clip), m_FarClip(far_clip), Camera(glm::perspective(glm::radians(fov), aspect_ratio, near_clip, far_clip))
    {
        UpdateView();
    }

    void EditorCamera::OnUpdate(Timestep ts)
    {
        if (Input::IsKeyPressed(ETHER_KEY_LEFT_ALT))
        {    
            const glm::vec2& mouse{ Input::GetMouseX(), Input::GetMouseY() };
            glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.003f;
            m_InitialMousePosition = mouse;

            //如果鼠标中键被点击，则相机平移
            if (Input::IsMouseButtonPressed(Mouse::ButtonMiddle))
            {
                MousePan(delta);
            }
            //如果左键被点击，则相机做pitch或者yaw旋转
            else if (Input::IsMouseButtonPressed(Mouse::ButtonLeft))
            {
                MouseRotate(delta);
            }
            //如果右键被点击，则相机根据delta.y的数值进行放大缩小
            else if (Input::IsMouseButtonPressed(Mouse::ButtonRight))
            {
                MouseZoom(delta.y);
            }
        }
        UpdateView();
    }

    void EditorCamera::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseScrolledEvent>(ETHER_BIND_EVENT_FN(OnMouseScrolled));
    }

    glm::vec3 EditorCamera::GetUpDirection() const
    {
        return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    glm::vec3 EditorCamera::GetRightDirection() const
    {
        return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
    }

    glm::vec3 EditorCamera::GetForwardDirection() const
    {
        return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
    }

    glm::quat EditorCamera::GetOrientation() const
    {
        //TOKNOW：这里为什么又变成负号了啊？？？
        //ANSWER: 因为要另画面随着鼠标的做同样角度的变化而不是反向角度的变化？
        return glm::quat(glm::vec3(-m_Pitch, -m_Yaw, 0.0f));
    }

    void Ether::EditorCamera::UpdateProjection()
    {
        m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
        m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
    }

    void EditorCamera::UpdateView()
    {
        m_Position = CalculatePosition();

        glm::quat orientation = GetOrientation();
        m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
        //这个m_ViewMatrix矩阵最终还是要作用到objects上，因此，对于相机所产上的变化矩阵作用在objects上是逆变换。
        m_ViewMatrix = glm::inverse(m_ViewMatrix);
    }

    bool EditorCamera::OnMouseScrolled(MouseScrolledEvent& e)
    {
        float delta = e.GetYOffset() * 0.1f;
        MouseZoom(delta);
        UpdateView();
        return false;
    }

    void EditorCamera::MousePan(const glm::vec2& delta)
    {
        auto [x_speed, y_speed] = PanSpeed();
        //TODO：为啥这里要是负数啊？？？能不能写明白点啊！！！！
        m_FocalPoint += -GetRightDirection() * delta.x * x_speed * m_Distance;
        m_FocalPoint += GetUpDirection() * delta.y * y_speed * m_Distance;
    }

    void EditorCamera::MouseRotate(const glm::vec2& delta)
    {
        float yaw_sign = GetUpDirection().y < 0.f ? -1.f : 1.f;
        m_Yaw += yaw_sign * delta.x * RotationSpeed();
        m_Pitch += delta.y * RotationSpeed();
    }

    void EditorCamera::MouseZoom(float delta)
    {
        //TODO: 这里的加减是他吗的怎么判定的啊？能不能给点信息来源啊
        //相机的位置和交点的距离是可以被鼠标缩放来改变的
        m_Distance -= delta * ZoomSpeed();
        //如果鼠标缩放导致m_Distance小于1.0f则进行纠正
        if (m_Distance < 1.0f)
        {
            m_FocalPoint += GetForwardDirection();
            m_Distance = 1.0f;
        }
    }

    glm::vec3 EditorCamera::CalculatePosition() const
    {
        return m_FocalPoint - GetForwardDirection() * m_Distance;
    }
    //TODO: 搞明白这个函数里边的数值为何如此设定？
    std::pair<float, float> EditorCamera::PanSpeed() const
    {
        float x = std::min(m_ViewportWidth / 1000.0f, 2.4f);    //max = 2.4f
        float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

        float y = std::min(m_ViewportHeight / 1000.0f, 2.4f);   //max = 2.4f
        float yFactor = 0.0366 * (y * y) - 0.1778f * y + 0.3021f;

        return { xFactor, yFactor };
    }
    //TODO: 搞明白这个函数里边的数值为何如此设定？
    float EditorCamera::RotationSpeed() const
    {
        return 0.8f;
    }
    //TODO: 搞明白这个函数里边的数值为何如此设定？
    float EditorCamera::ZoomSpeed() const
    {
        float distance = m_Distance * 0.2f;
        distance = std::max(distance, 0.0f);
        float speed = distance * distance;
        speed = std::min(speed, 100.f);
        return speed;
    }
}