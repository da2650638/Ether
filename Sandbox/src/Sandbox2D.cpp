#include "Sandbox2D.h"

#include "imgui.h"

Sandbox2D::Sandbox2D(const std::string& debugName)
	: Layer(debugName),
	m_OrthographicCameraController(16.0f / 9.0f),
	m_BgTilingFactor(10.0f),
	m_BgTintColor({ 1.0f, 1.0f, 1.0f, 1.0f }),
	m_BgRotation(0.0f)
{
}

void Sandbox2D::OnAttach()
{
	ETHER_PROFILE_FUNCTION();
	//Ether::Renderer2D::Init();
	m_Texture1 = Ether::Texture2D::Create("assets/textures/Checkerboard.png");
	m_Texture2 = Ether::Texture2D::Create("assets/textures/ChernoLogo.png");
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
		Ether::Renderer2D::ResetStats();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		ETHER_PROFILE_SCOPE("Renderer Draw");
		Ether::Renderer2D::BeginScene(m_OrthographicCameraController.GetCamera());
		Ether::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		Ether::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Ether::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Ether::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.2f }, { 20.0f, 20.0f }, m_Texture1, 20.0f);
		Ether::Renderer2D::DrawRotatedQuad({ -0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_Texture1, 20.0f);
		Ether::Renderer2D::EndScene();

		Ether::Renderer2D::BeginScene(m_OrthographicCameraController.GetCamera());
		for (float y = -4.75; y < 5.25; y += 0.5)
		{
			for (float x = -4.75; x < 5.25; x += 0.5)
			{
				Ether::Renderer2D::DrawQuad({ x, y, -0.1f }, { 0.45f, 0.45f }, { (x + 4.75) / 10.0f, (y + 4.75) / 10.0f, 0.3f, 0.7f });
			}
		}
		Ether::Renderer2D::EndScene();
	}	
}

void Sandbox2D::OnImGuiRender()
{
	ETHER_PROFILE_FUNCTION();

	ImGui::Begin("Settings");

	auto stats = Ether::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::End();
}

void Sandbox2D::OnEvent(Ether::Event& e)
{
	m_OrthographicCameraController.OnEvent(e);
}
