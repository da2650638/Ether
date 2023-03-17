#pragma once
#include "Event.h"

namespace Ether {

	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(uint32_t x, uint32_t y)
			: m_MouseX(x), m_MouseY(y){}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		virtual std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: (" << m_MouseX << ", " << m_MouseY << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset){}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: [" << m_XOffset << ", " << m_YOffset << "]";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event {
	public:
		inline int GetButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouseButton)
	protected:
		MouseButtonEvent(int button)
			: m_Button(button) {}

		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button << " pressed.";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button)	{}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleased: " << m_Button << " released.";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}