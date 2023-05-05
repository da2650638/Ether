#include "Ether.h"

#include "imgui.h"

class SandboxLayer : public Ether::Layer {
public:
	SandboxLayer(const std::string& debugName)
		: Ether::Layer(debugName)
	{

	}

	virtual void OnUpdate() override
	{
		if (Ether::Input::IsKeyPressed(ETHER_KEY_TAB))
		{
			ETHER_INFO("Key Tab is pressed.");
		}
	}
	//只是简单的将事件信息打印出来
	virtual void OnEvent(Ether::Event& e) override
	{
		ETHER_INFO("Sandbox Layer:[{0}]", e);
	}

	virtual void OnImGuiRender() override
	{
		ImGui::ShowDemoWindow();
	}
private:

};

class Sandbox : public Ether::Application
{
public:
	Sandbox()
	{
		PushLayer(new SandboxLayer("SandboxLayer"));
	}

	virtual ~Sandbox()
	{

	}
};

Ether::Application* Ether::CreateApplication()
{
	return new Sandbox();
}