#include "Ether.h"
#include "Ether/Core/EntryPoint.h"

#include "imgui.h"

#include "EditorLayer.h"

namespace Ether {

	class Editor : public Application
	{
	public:
		Editor()
		{
			//PushLayer(new SandboxLayer("SandboxLayer"));
			PushLayer(new EditorLayer("Ether-Editor"));
		}

		virtual ~Editor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new Editor();
	}

}