#include "Ether.h"

#include "imgui.h"

class SandboxLayer : public Ether::Layer {
public:
	SandboxLayer(const std::string& debugName)
		: Ether::Layer(debugName)
	{
		float vertices[] = {
			//Position          //color           //texCoord
			-0.5f, -0.5f,0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.5f,  -0.5f,0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f
		};
		uint32_t indices[] = {
			0, 1, 2,
			1, 2, 3
		};
		m_VertexBuffer.reset(Ether::VertexBuffer::Create(vertices, sizeof(vertices)));
		m_IndexBuffer.reset(Ether::IndexBuffer::Create(indices, sizeof(indices)));
		{
			Ether::BufferLayout layout = { {Ether::ShaderDataType::Float3, "a_Position"}, {Ether::ShaderDataType::Float3, "a_Color"}, {Ether::ShaderDataType::Float2, "a_TexCoord"}};
			m_VertexBuffer->SetLayout(layout);
		}
		m_VertexArray.reset(Ether::VertexArray::Create());
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		m_ShaderLibrary.reset( new Ether::ShaderLibrary() );
		m_ShaderLibrary->Load("Simple Shader", "assets/shaders/VertexShader.glsl", "assets/shaders/FragmentShader.glsl");
		m_Texture1 = Ether::Texture2D::Create("assets/textures/Checkerboard.png");
		m_Texture2 = Ether::Texture2D::Create("assets/textures/ChernoLogo.png");
	}
	
	virtual void OnAttach() override
	{

	}

	virtual void OnDetach() override
	{

	}

	virtual void OnUpdate(Ether::Timestep ts) override
	{
		Ether::Renderer::Clear();
		Ether::Renderer::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		m_VertexArray->Bind();
		auto simple_shader = (*m_ShaderLibrary)["Simple Shader"];
		simple_shader->Bind();
		std::dynamic_pointer_cast<Ether::OpenGLShader>(simple_shader)->UploadUniformInt("u_Texture", 0);
		m_Texture1->Bind(0);
		Ether::RenderCommand::DrawIndexed(m_VertexArray);
		m_Texture2->Bind(0);
		Ether::RenderCommand::DrawIndexed(m_VertexArray);
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
	Ether::Ref<Ether::ShaderLibrary> m_ShaderLibrary;
	Ether::Ref<Ether::Texture2D> m_Texture1, m_Texture2;
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