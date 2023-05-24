#include "Sandbox2D.h"

#include "imgui.h"

Sandbox2D::Sandbox2D(const std::string& debugName)
	: Layer(debugName),
	  m_OrthographicCameraController(16.0f / 9.0f)
{
}

void Sandbox2D::OnAttach()
{
	Ether::Renderer2D::Init();
	m_Texture1 = Ether::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	Ether::Renderer2D::ShutDown();
}

void Sandbox2D::OnUpdate(Ether::Timestep ts)
{
	Ether::Renderer::Clear();
	Ether::Renderer::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	m_OrthographicCameraController.OnUpdate(ts);

	Ether::Renderer2D::BeginScene(m_OrthographicCameraController.GetCamera());

	Ether::Renderer2D::DrawQuad({ -0.15f, 0.0f }, { 0.3f, 0.3f }, glm::vec4(1.0f));
	Ether::Renderer2D::DrawQuad({ 0.15f, 0.0f }, { 0.3f, 0.3f }, glm::vec4(1.0f));

	Ether::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f ,10.0f }, m_Texture1);

	Ether::Renderer2D::EndScene();
	
}

void Sandbox2D::OnImGuiRender()
{

}

void Sandbox2D::OnEvent(Ether::Event& e)
{
	m_OrthographicCameraController.OnEvent(e);
}
