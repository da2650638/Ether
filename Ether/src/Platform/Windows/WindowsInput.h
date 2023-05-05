#pragma once

#include "Ether/Input.h"

namespace Ether
{
	class ETHER_API WindowsInput : public Input
	{
	public:
		WindowsInput() = default;
		~WindowsInput() = default;
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}