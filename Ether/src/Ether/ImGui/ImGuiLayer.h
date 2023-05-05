#pragma once

#include "Ether/Layer.h"

namespace Ether
{
	class ETHER_API ImGuiLayer : public Layer
	{
	public:
		//The function of the ImGuiLayer is to initialize the ImGui and clean up the ImGui with function Begin() and End().
		ImGuiLayer(const std::string& debugName = "ImGuiLayer");
		virtual ~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();
	};
}