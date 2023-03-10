#pragma once
#include "Ether/Core.h"

#include <string>
#include <functional>

namespace Ether {

	enum EventType {
		NoneType = 0,
		WindowResize, WindowClose, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseMoved, MouseScrolled, MouseButtonPressed, MouseButtonReleased
	};

	enum EventCategory {
		NoneCategory = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput =       BIT(1),
		EventCategoryKeyBoard =    BIT(2),
		EventCategoryMouse =       BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; } \
                               virtual EventType GetType() const override { return GetStaticType(); } \
                               virtual const char* GetName() const override { return #type; }


#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event {
		friend class EventDispatcher;
	public:
		virtual EventType GetType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual const std::string& ToString() const { return GetName(); }
		bool IsInCategory(EventCategory category) {
			return category & GetCategoryFlags();
		}

	private:
		bool m_Handled = false;
	};

	class EventDispatcher {
		template <typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template <typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetType() == T::GetStaticType()) {
				m_Event.m_Handled = func(*((T*)(&m_Event)));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};
}