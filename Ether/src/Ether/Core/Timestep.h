#pragma once

#include "Ether/Core/Core.h"

namespace Ether
{
	class ETHER_API Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMillSeconds() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};
}