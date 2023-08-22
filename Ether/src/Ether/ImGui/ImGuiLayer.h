#pragma once

#include "Ether/Core/Layer.h"

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
		virtual void OnEvent(Event& e) override;
		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();
	private:
		bool m_BlockEvents = true;
	};
}