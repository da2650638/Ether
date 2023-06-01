#pragma once

namespace Ether
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

#define ETHER_KEY_SPACE           ::Ether::Key::Space
#define ETHER_KEY_APOSTROPHE      ::Ether::Key::Apostrophe    /* ' */
#define ETHER_KEY_COMMA           ::Ether::Key::Comma         /* , */
#define ETHER_KEY_MINUS           ::Ether::Key::Minus         /* - */
#define ETHER_KEY_PERIOD          ::Ether::Key::Period        /* . */
#define ETHER_KEY_SLASH           ::Ether::Key::Slash         /* / */
#define ETHER_KEY_0               ::Ether::Key::D0
#define ETHER_KEY_1               ::Ether::Key::D1
#define ETHER_KEY_2               ::Ether::Key::D2
#define ETHER_KEY_3               ::Ether::Key::D3
#define ETHER_KEY_4               ::Ether::Key::D4
#define ETHER_KEY_5               ::Ether::Key::D5
#define ETHER_KEY_6               ::Ether::Key::D6
#define ETHER_KEY_7               ::Ether::Key::D7
#define ETHER_KEY_8               ::Ether::Key::D8
#define ETHER_KEY_9               ::Ether::Key::D9
#define ETHER_KEY_SEMICOLON       ::Ether::Key::Semicolon     /* ; */
#define ETHER_KEY_EQUAL           ::Ether::Key::Equal         /* = */
#define ETHER_KEY_A               ::Ether::Key::A
#define ETHER_KEY_B               ::Ether::Key::B
#define ETHER_KEY_C               ::Ether::Key::C
#define ETHER_KEY_D               ::Ether::Key::D
#define ETHER_KEY_E               ::Ether::Key::E
#define ETHER_KEY_F               ::Ether::Key::F
#define ETHER_KEY_G               ::Ether::Key::G
#define ETHER_KEY_H               ::Ether::Key::H
#define ETHER_KEY_I               ::Ether::Key::I
#define ETHER_KEY_J               ::Ether::Key::J
#define ETHER_KEY_K               ::Ether::Key::K
#define ETHER_KEY_L               ::Ether::Key::L
#define ETHER_KEY_M               ::Ether::Key::M
#define ETHER_KEY_N               ::Ether::Key::N
#define ETHER_KEY_O               ::Ether::Key::O
#define ETHER_KEY_P               ::Ether::Key::P
#define ETHER_KEY_Q               ::Ether::Key::Q
#define ETHER_KEY_R               ::Ether::Key::R
#define ETHER_KEY_S               ::Ether::Key::S
#define ETHER_KEY_T               ::Ether::Key::T
#define ETHER_KEY_U               ::Ether::Key::U
#define ETHER_KEY_V               ::Ether::Key::V
#define ETHER_KEY_W               ::Ether::Key::W
#define ETHER_KEY_X               ::Ether::Key::X
#define ETHER_KEY_Y               ::Ether::Key::Y
#define ETHER_KEY_Z               ::Ether::Key::Z
#define ETHER_KEY_LEFT_BRACKET    ::Ether::Key::LeftBracket   /* [ */
#define ETHER_KEY_BACKSLASH       ::Ether::Key::Backslash     /* \ */
#define ETHER_KEY_RIGHT_BRACKET   ::Ether::Key::RightBracket  /* ] */
#define ETHER_KEY_GRAVE_ACCENT    ::Ether::Key::GraveAccent   /* ` */
#define ETHER_KEY_WORLD_1         ::Ether::Key::World1        /* non-US #1 */
#define ETHER_KEY_WORLD_2         ::Ether::Key::World2        /* non-US #2 */
//Function Keys
#define ETHER_KEY_ESCAPE          ::Ether::Key::Escape
#define ETHER_KEY_ENTER           ::Ether::Key::Enter
#define ETHER_KEY_TAB             ::Ether::Key::Tab
#define ETHER_KEY_BACKSPACE       ::Ether::Key::Backspace
#define ETHER_KEY_INSERT          ::Ether::Key::Insert
#define ETHER_KEY_DELETE          ::Ether::Key::Delete
#define ETHER_KEY_RIGHT           ::Ether::Key::Right
#define ETHER_KEY_LEFT            ::Ether::Key::Left
#define ETHER_KEY_DOWN            ::Ether::Key::Down
#define ETHER_KEY_UP              ::Ether::Key::Up
#define ETHER_KEY_PAGE_UP         ::Ether::Key::PageUp
#define ETHER_KEY_PAGE_DOWN       ::Ether::Key::PageDown
#define ETHER_KEY_HOME            ::Ether::Key::Home
#define ETHER_KEY_END             ::Ether::Key::End
#define ETHER_KEY_CAPS_LOCK       ::Ether::Key::CapsLock
#define ETHER_KEY_SCROLL_LOCK     ::Ether::Key::ScrollLock
#define ETHER_KEY_NUM_LOCK        ::Ether::Key::NumLock
#define ETHER_KEY_PRINT_SCREEN    ::Ether::Key::PrintScreen
#define ETHER_KEY_PAUSE           ::Ether::Key::Pause
#define ETHER_KEY_F1              ::Ether::Key::F1
#define ETHER_KEY_F2              ::Ether::Key::F2
#define ETHER_KEY_F3              ::Ether::Key::F3
#define ETHER_KEY_F4              ::Ether::Key::F4
#define ETHER_KEY_F5              ::Ether::Key::F5
#define ETHER_KEY_F6              ::Ether::Key::F6
#define ETHER_KEY_F7              ::Ether::Key::F7
#define ETHER_KEY_F8              ::Ether::Key::F8
#define ETHER_KEY_F9              ::Ether::Key::F9
#define ETHER_KEY_F10             ::Ether::Key::F10
#define ETHER_KEY_F11             ::Ether::Key::F11
#define ETHER_KEY_F12             ::Ether::Key::F12
#define ETHER_KEY_F13             ::Ether::Key::F13
#define ETHER_KEY_F14             ::Ether::Key::F14
#define ETHER_KEY_F15             ::Ether::Key::F15
#define ETHER_KEY_F16             ::Ether::Key::F16
#define ETHER_KEY_F17             ::Ether::Key::F17
#define ETHER_KEY_F18             ::Ether::Key::F18
#define ETHER_KEY_F19             ::Ether::Key::F19
#define ETHER_KEY_F20             ::Ether::Key::F20
#define ETHER_KEY_F21             ::Ether::Key::F21
#define ETHER_KEY_F22             ::Ether::Key::F22
#define ETHER_KEY_F23             ::Ether::Key::F23
#define ETHER_KEY_F24             ::Ether::Key::F24
#define ETHER_KEY_F25             ::Ether::Key::F25

/* Keypad */
#define ETHER_KEY_KP_0            ::Ether::Key::KP0
#define ETHER_KEY_KP_1            ::Ether::Key::KP1
#define ETHER_KEY_KP_2            ::Ether::Key::KP2
#define ETHER_KEY_KP_3            ::Ether::Key::KP3
#define ETHER_KEY_KP_4            ::Ether::Key::KP4
#define ETHER_KEY_KP_5            ::Ether::Key::KP5
#define ETHER_KEY_KP_6            ::Ether::Key::KP6
#define ETHER_KEY_KP_7            ::Ether::Key::KP7
#define ETHER_KEY_KP_8            ::Ether::Key::KP8
#define ETHER_KEY_KP_9            ::Ether::Key::KP9
#define ETHER_KEY_KP_DECIMAL      ::Ether::Key::KPDecimal
#define ETHER_KEY_KP_DIVIDE       ::Ether::Key::KPDivide
#define ETHER_KEY_KP_MULTIPLY     ::Ether::Key::KPMultiply
#define ETHER_KEY_KP_SUBTRACT     ::Ether::Key::KPSubtract
#define ETHER_KEY_KP_ADD          ::Ether::Key::KPAdd
#define ETHER_KEY_KP_ENTER        ::Ether::Key::KPEnter
#define ETHER_KEY_KP_EQUAL        ::Ether::Key::KPEqual

#define ETHER_KEY_LEFT_SHIFT      ::Ether::Key::LeftShift
#define ETHER_KEY_LEFT_CONTROL    ::Ether::Key::LeftControl
#define ETHER_KEY_LEFT_ALT        ::Ether::Key::LeftAlt
#define ETHER_KEY_LEFT_SUPER      ::Ether::Key::LeftSuper
#define ETHER_KEY_RIGHT_SHIFT     ::Ether::Key::RightShift
#define ETHER_KEY_RIGHT_CONTROL   ::Ether::Key::RightControl
#define ETHER_KEY_RIGHT_ALT       ::Ether::Key::RightAlt
#define ETHER_KEY_RIGHT_SUPER     ::Ether::Key::RightSuper
#define ETHER_KEY_MENU            ::Ether::Key::Menu