#pragma once

#include "Ether.h"

namespace Ether
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() {}
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		const Entity& GetSelectionContext() const { return m_SelectionContext; }
		
		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}