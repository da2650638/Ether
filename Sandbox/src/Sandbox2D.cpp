#include "Sandbox2D.h"

#include "imgui.h"

Sandbox2D::Sandbox2D(const std::string& debugName)
	: Layer(debugName),
	  m_OrthographicCameraController(16.0f / 9.0f)
{
}

void Sandbox2D::OnAttach()
{
	ETHER_PROFILE_FUNCTION();
	//Ether::Renderer2D::Init();
	m_Texture1 = Ether::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	ETHER_PROFILE_FUNCTION();
	//Ether::Renderer2D::ShutDown();
}

void Sandbox2D::OnUpdate(Ether::Timestep ts)
{
	ETHER_PROFILE_FUNCTION();

	{
		ETHER_PROFILE_SCOPE("CameraController::OnUpdate");
		m_OrthographicCameraController.OnUpdate(ts);
	}
	
	{
		ETHER_PROFILE_SCOPE("Renderer Prep");
		Ether::Renderer::Clear();
		Ether::Renderer::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
	}

	{
		ETHER_PROFILE_SCOPE("Renderer Draw");
		Ether::Renderer2D::BeginScene(m_OrthographicCameraController.GetCamera());

		Ether::Renderer2D::DrawQuad({ -0.15f, 0.0f }, { 0.3f, 0.3f }, {0.2f, 0.3f, 0.8f, 1.0f});
		Ether::Renderer2D::DrawQuad({ 0.15f, 0.0f }, { 0.3f, 0.3f }, {0.8f, 0.3f, 0.2f, 1.0f});

		Ether::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 200.0f ,200.0f }, m_Texture1);

		Ether::Renderer2D::EndScene();
	}	
}

void Sandbox2D::OnImGuiRender()
{

}

void Sandbox2D::OnEvent(Ether::Event& e)
{
	m_OrthographicCameraController.OnEvent(e);
}
