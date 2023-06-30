#pragma once

#include "Ether/Core/Base.h"
#include "Ether/Core/MouseCodes.h"
#include "Ether/Core/KeyCodes.h"

namespace Ether
{
	class ETHER_API Input
	{
	public:
		Input() = default;
		~Input() = default;
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}