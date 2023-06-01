#pragma once

#include <stdint.h>
#include <iostream>

namespace Ether
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	}Mouse;

	inline std::ostream& operator<<(std::ostream& out, MouseCode mouseCode)
	{
		out << static_cast<int32_t>(mouseCode);
		return out;
	}

#define ETHER_MOUSE_BUTTON_0      ::Ether::Mouse::Button0
#define ETHER_MOUSE_BUTTON_1      ::Ether::Mouse::Button1
#define ETHER_MOUSE_BUTTON_2      ::Ether::Mouse::Button2
#define ETHER_MOUSE_BUTTON_3      ::Ether::Mouse::Button3
#define ETHER_MOUSE_BUTTON_4      ::Ether::Mouse::Button4
#define ETHER_MOUSE_BUTTON_5      ::Ether::Mouse::Button5
#define ETHER_MOUSE_BUTTON_6      ::Ether::Mouse::Button6
#define ETHER_MOUSE_BUTTON_7      ::Ether::Mouse::Button7
#define ETHER_MOUSE_BUTTON_LAST   ::Ether::Mouse::ButtonLast
#define ETHER_MOUSE_BUTTON_LEFT   ::Ether::Mouse::ButtonLeft
#define ETHER_MOUSE_BUTTON_RIGHT  ::Ether::Mouse::ButtonRight
#define ETHER_MOUSE_BUTTON_MIDDLE ::Ether::Mouse::ButtonMiddle
}