#pragma once

#include "Ether/Layer.h"

namespace Ether
{
	class ETHER_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(const std::string& debugName = "ImGuiLayer");
		virtual ~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();
	};
}