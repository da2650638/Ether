#include "Ether.h"
#include "Ether/Core/EntryPoint.h"

#include "imgui.h"

#include "Sandbox2D.h"

class SandboxLayer : public Ether::Layer {
public:
	SandboxLayer(const std::string& debugName)
		: Ether::Layer(debugName),
		m_OrthographicCameraController(16.0f / 9.0f, true)
	{

	}
	
	virtual void OnAttach() override
	{
		float vertices[] = {
			//Position          //color           //texCoord
			-0.4f, -0.4f,0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			0.4f,  -0.4f,0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
			-0.4f, 0.4f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.4f,  0.4f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f
		};
		uint32_t indices[] = {
			0, 1, 2,
			1, 2, 3
		};
		m_VertexBuffer = Ether::VertexBuffer::Create(vertices, sizeof(vertices));
		m_IndexBuffer = Ether::IndexBuffer::Create(indices, sizeof(indices));
		{
			Ether::BufferLayout layout = { {Ether::ShaderDataType::Float3, "a_Position"}, {Ether::ShaderDataType::Float3, "a_Color"}, {Ether::ShaderDataType::Float2, "a_TexCoord"} };
			m_VertexBuffer->SetLayout(layout);
		}
		m_VertexArray = Ether::VertexArray::Create();
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
		m_ShaderLibrary.reset(new Ether::ShaderLibrary());
		m_ShaderLibrary->Load("Texture Shader", "assets/shaders/VertexShader.glsl", "assets/shaders/Texture2DFragmentShader.glsl");
		m_ShaderLibrary->Load("Flat Color Shader", "assets/shaders/VertexShader.glsl", "assets/shaders/FlatColorFragmentColor.glsl");
		m_Texture1 = Ether::Texture2D::Create("assets/textures/Checkerboard.png");
		m_Texture2 = Ether::Texture2D::Create("assets/textures/ChernoLogo.png");
	}

	virtual void OnDetach() override
	{

	}

	virtual void OnUpdate(Ether::Timestep ts) override
	{
		Ether::Renderer::Clear();
		Ether::Renderer::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });

		Ether::Renderer::BeginScene(m_OrthographicCameraController.GetCamera());

		auto texture_shader = (*m_ShaderLibrary)["Texture Shader"];
		glm::mat4 transform(1.0f);
		//一定要先绑定Shader的值，在设置里边的Uniform

		Ether::Renderer::Submit(texture_shader, m_VertexArray, glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f)));
		std::dynamic_pointer_cast<Ether::OpenGLShader>(texture_shader)->UploadUniformInt("u_Texture", 0);
		m_Texture1->Bind(0);
		
		Ether::Renderer::Submit(texture_shader, m_VertexArray, glm::translate(transform, glm::vec3(0.5f, 0.5f, 0.0f)));
		std::dynamic_pointer_cast<Ether::OpenGLShader>(texture_shader)->UploadUniformInt("u_Texture", 0);
		m_Texture2->Bind(0);
		

		auto flat_color_shader = (*m_ShaderLibrary)["Flat Color Shader"];
		Ether::Renderer::Submit(flat_color_shader, m_VertexArray, glm::translate(transform, glm::vec3(-0.5f, -0.5f, 0.0f)));
		std::dynamic_pointer_cast<Ether::OpenGLShader>(flat_color_shader)->UploadUniformFloat3("u_Color", glm::vec3(1.0f, 1.0f, 0.0f));

		Ether::Renderer::Submit(flat_color_shader, m_VertexArray, glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f)));
		std::dynamic_pointer_cast<Ether::OpenGLShader>(flat_color_shader)->UploadUniformFloat3("u_Color", glm::vec3(1.0f, 0.0f, 0.0f));

		m_OrthographicCameraController.OnUpdate(ts);
		Ether::Renderer::EndScene();
	}
	//只是简单的将事件信息打印出来
	virtual void OnEvent(Ether::Event& e) override
	{
		m_OrthographicCameraController.OnEvent(e);
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
	Ether::OrthographicCameraController m_OrthographicCameraController;
};

class Sandbox : public Ether::Application
{
public:
	Sandbox()
	{
		//PushLayer(new SandboxLayer("SandboxLayer"));
		PushLayer(new Sandbox2D("Sandbox2D"));
	}

	virtual ~Sandbox()
	{

	}
};

Ether::Application* Ether::CreateApplication()
{
	return new Sandbox();
}