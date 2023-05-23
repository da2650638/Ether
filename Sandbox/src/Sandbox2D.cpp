#include "Sandbox2D.h"

#include "imgui.h"

Sandbox2D::Sandbox2D(const std::string& debugName)
	: Layer(debugName),
	  m_OrthographicCameraController(16.0f / 9.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	float vertices[] = {
		//Position         
		-0.5f, -0.5f,0.0f, 
		0.5f,  -0.5f,0.0f, 
		-0.5f, 0.5f, 0.0f, 
		0.5f,  0.5f, 0.0f 
	};
	uint32_t indices[] = {
		0, 1, 2,
		1, 2, 3
	};

	Ether::Ref<Ether::VertexBuffer> vb = Ether::VertexBuffer::Create(vertices, sizeof(vertices));
	Ether::BufferLayout layout = { {Ether::ShaderDataType::Float3, "a_Position"} };
	vb->SetLayout(layout);
	Ether::Ref<Ether::IndexBuffer> ib = Ether::IndexBuffer::Create(indices, sizeof(indices));

	m_VertexArray = Ether::VertexArray::Create();
	m_VertexArray->AddVertexBuffer(vb);
	m_VertexArray->SetIndexBuffer(ib);

	m_ShaderLibrary.reset(new Ether::ShaderLibrary());
	m_ShaderLibrary->Load("Sandbox2D", "assets/shaders/Sandbox2D_Vert.glsl", "assets/shaders/Sandbox2D_Frag.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Ether::Timestep ts)
{
	Ether::Renderer::Clear();
	Ether::Renderer::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	m_OrthographicCameraController.OnUpdate(ts);
	Ether::Renderer::BeginScene(m_OrthographicCameraController.GetCamera());
	auto shader = (*m_ShaderLibrary)["Sandbox2D"];
	glm::mat4 transform(1.0f);
	shader->Bind();
	std::dynamic_pointer_cast<Ether::OpenGLShader>(shader)->UploadUniformFloat4("u_Color", m_Color);
	Ether::Renderer::Submit(shader, m_VertexArray, transform);
	Ether::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("SquareColor:", glm::value_ptr(m_Color));
	ImGui::End();
}

void Sandbox2D::OnEvent(Ether::Event& e)
{
	m_OrthographicCameraController.OnEvent(e);
}
