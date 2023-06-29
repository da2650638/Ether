#include "EditorLayer.h"

#include "imgui.h"

namespace Ether {

	EditorLayer::EditorLayer(const std::string& debugName)
		: Layer(debugName),
		m_OrthographicCameraController(1280.0f / 720.0f),
		m_BgTilingFactor(10.0f),
		m_BgTintColor({ 1.0f, 1.0f, 1.0f, 1.0f }),
		m_BgRotation(0.0f)
	{
	}

	void EditorLayer::OnAttach()
	{
		ETHER_PROFILE_FUNCTION();
		//Renderer2D::Init();
		m_Texture1 = Texture2D::Create("assets/textures/Checkerboard.png");
		m_Texture2 = Texture2D::Create("assets/textures/ChernoLogo.png");

		FramebufferSpecification spec;
		spec.Width = 1280;
		spec.Height = 720;
		m_Framebuffer = Framebuffer::Create(spec);
	}

	void EditorLayer::OnDetach()
	{
		ETHER_PROFILE_FUNCTION();
		//Renderer2D::ShutDown();
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		ETHER_PROFILE_FUNCTION();

		{
			ETHER_PROFILE_SCOPE("CameraController::OnUpdate");
			m_OrthographicCameraController.OnUpdate(ts);
		}

		{
			ETHER_PROFILE_SCOPE("Renderer Prep");
			m_Framebuffer->Bind();
			Renderer::Clear();
			Renderer::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
			Renderer2D::ResetStats();
		}

		{
			static float rotation = 0.0f;
			rotation += ts * 50.0f;

			ETHER_PROFILE_SCOPE("Renderer Draw");
			Renderer2D::BeginScene(m_OrthographicCameraController.GetCamera());
			Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
			Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
			Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
			Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.2f }, { 20.0f, 20.0f }, m_Texture1, 20.0f);
			Renderer2D::DrawRotatedQuad({ -0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_Texture1, 1.0f);
			Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.2f, 0.3f, 0.8f, 1.0f });
			Renderer2D::EndScene();

			Renderer2D::BeginScene(m_OrthographicCameraController.GetCamera());
			for (float y = -4.75; y < 5.25; y += 0.5)
			{
				for (float x = -4.75; x < 5.25; x += 0.5)
				{
					Renderer2D::DrawQuad({ x, y, 0.0f }, { 0.45f, 0.45f }, { (x + 4.75) / 10.0f, (y + 4.75) / 10.0f, 0.3f, 1.0f });
				}
			}
			Renderer2D::EndScene();
			m_Framebuffer->UnBind();
		}
	}

	void EditorLayer::OnImGuiRender()
	{
		ETHER_PROFILE_FUNCTION();

		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		bool show_dock_space = true;
		ImGui::Begin("DockSpace Demo", &show_dock_space, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		else
		{
			ImGuiIO& io = ImGui::GetIO();
			ImGui::Text("ERROR: Docking is not enabled! See Demo > Configuration.");
			ImGui::Text("Set io.ConfigFlags |= ImGuiConfigFlags_DockingEnable in your code, or ");
			ImGui::SameLine(0.0f, 0.0f);
			if (ImGui::SmallButton("click here"))
				io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Options"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
				ImGui::MenuItem("Padding", NULL, &opt_padding);
				ImGui::Separator();

				if (ImGui::MenuItem("Close", NULL, false, &show_dock_space != NULL))
					Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

		ImGui::Begin("Viewport");
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize))
		{
			m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

			m_OrthographicCameraController.OnResize(viewportPanelSize.x, viewportPanelSize.y);
		}
		uint32_t textureID = m_Framebuffer->GetColorAttachment();
		ImGui::Image((void*)textureID, ImVec2{ m_ViewportSize.x, m_ViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_OrthographicCameraController.OnEvent(e);
	}

}
