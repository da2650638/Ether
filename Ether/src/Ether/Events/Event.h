#pragma once
#include "etherpch.h"
#include "Ether/Core/Core.h"

namespace Ether {

	//Events in Ether are currently blocking, meaning when an event occurs it
    //immediately gets dispatched and must be dealt with right then an there.
    //For the future, a better strategy might be to buffer events in an event
    //bus and process them during the "event" part of the update stage.

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

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; } \
                               virtual EventType GetType() const override { return GetStaticType(); } \
                               virtual const char* GetName() const override { return #type; }


#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event {
		friend class EventDispatcher;
	public:
		bool Handled = false;
		virtual EventType GetType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
		bool IsInCategory(EventCategory category) {
			return category & GetCategoryFlags();
		}
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
				m_Event.Handled = func(*((T*)(&m_Event)));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};
	//重载输出运算符，保证spdlog可以输出Event的日志。
	inline std::ostream& operator<<(std::ostream& out, const Event& e)
	{
		out << e.ToString();
		return out;
	}
}