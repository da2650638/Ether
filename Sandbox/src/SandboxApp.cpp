#include "Ether.h"

#include "imgui.h"
//TODO: OpenGL specificed code should be here
#include <glad/glad.h>

class SandboxLayer : public Ether::Layer {
public:
	SandboxLayer(const std::string& debugName)
		: Ether::Layer(debugName)
	{
		//These code shouldn't be here.
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
		m_VertexBuffer.reset(new Ether::OpenGLVertexBuffer(vertices, sizeof(vertices)));
		m_IndexBuffer.reset(new Ether::OpenGLIndexBuffer(indices, sizeof(indices) / sizeof(uint32_t)));
		{
			Ether::BufferLayout layout = { {Ether::ShaderDataType::Float3, "a_Position"} };
			m_VertexBuffer->SetLayout(layout);
		}
		uint32_t index = 0;
		uint32_t stride = m_VertexBuffer->GetLayout().GetStride();
		for (const auto& element : m_VertexBuffer->GetLayout())
		{
			glVertexAttribPointer(
				0,
				element.GetElementCount(),
				Ether::ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				stride,
				(void*)element.Offset);
			glEnableVertexAttribArray(index);
			index++;
		}
	}

	virtual void OnUpdate() override
	{
		//TODO: OpenGL specificed codes shouldn't be here.
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
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
	Ether::Ref<Ether::VertexBuffer> m_VertexBuffer;
	Ether::Ref<Ether::IndexBuffer> m_IndexBuffer;
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