#include "Ether.h"

#include "imgui.h"

class SandboxLayer : public Ether::Layer {
public:
	SandboxLayer(const std::string& debugName)
		: Ether::Layer(debugName)
	{
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f,  -0.5f, 0.0f,
			-0.5f,  0.5f,  0.0f,
			0.5f,  0.5f,  0.0f
		};
		uint32_t indices[] = {
			0, 1, 2,
			1, 2, 3
		};
		m_VertexBuffer.reset(Ether::VertexBuffer::Create(vertices, sizeof(vertices)));
		m_IndexBuffer.reset(Ether::IndexBuffer::Create(indices, sizeof(indices)));
		{
			Ether::BufferLayout layout = { {Ether::ShaderDataType::Float3, "a_Position"} };
			m_VertexBuffer->SetLayout(layout);
		}
		m_VertexArray.reset(Ether::VertexArray::Create());
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	}
	
	virtual void OnAttach() override
	{

	}

	virtual void OnDetach() override
	{

	}

	virtual void OnUpdate(Ether::Timestep ts) override
	{
		Ether::RenderCommand::DrawIndexed(m_VertexArray);
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
		//ImGui::ShowDemoWindow();
	}
private:
	Ether::Ref<Ether::VertexBuffer> m_VertexBuffer;
	Ether::Ref<Ether::IndexBuffer> m_IndexBuffer;
	Ether::Ref<Ether::VertexArray> m_VertexArray;
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