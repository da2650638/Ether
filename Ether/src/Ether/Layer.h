#pragma once

#include "Ether/Core.h"
#include "Ether/Events/Event.h"

namespace Ether
{
	class ETHER_API Layer {
	public:
		Layer(const std::string& debugName);

		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		//�Ժ�Ҳ���ܼ�����ӱ�Ŀ�ܵĶ���
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

	private:
		std::string m_DebugName;
	};
}