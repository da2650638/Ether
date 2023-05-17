#pragma once

#include "Ether/Core/Core.h"
#include "Ether/Events/Event.h"
#include "Ether/Core/Timestep.h"

namespace Ether
{
	class ETHER_API Layer {
	public:
		Layer(const std::string& debugName);

		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		//以后也可能继续添加别的框架的东西
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

	private:
		std::string m_DebugName;
	};
}