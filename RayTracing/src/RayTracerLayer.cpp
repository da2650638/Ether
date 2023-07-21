#include "RayTracerLayer.h"

#include "imgui.h"

namespace Ether
{
	Ether::RayTracerLayer::RayTracerLayer(const std::string& name)
		: Layer(name),
		  m_OrthographicCameraController(1280.0f / 720.0f)
	{

	}

	void RayTracerLayer::OnAttach()
	{
		ETHER_PROFILE_FUNCTION();

		m_Image = Image::Create(1280, 720);

		FramebufferSpecification spec;
		spec.Width = 1280;
		spec.Height = 720;
		m_Framebuffer = Framebuffer::Create(spec);

		m_BackgroundTexture = Texture2D::Create("assets/textures/bg1.jpg");
	}

	void RayTracerLayer::OnDetach()
	{
		
	}

	void RayTracerLayer::OnUpdate(Timestep ts)
	{
		ETHER_PROFILE_SCOPE("RayTracerLayer::OnUpdate");
		m_Framebuffer->Bind();
		Renderer::Clear();
		Renderer::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		Renderer2D::ResetStats();

		Renderer2D::BeginScene(m_OrthographicCameraController.GetCamera());
		Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.2f }, { 2.0f * m_OrthographicCameraController.GetAspectRatio(), 2.0f}, m_BackgroundTexture, 1.0f);
		Renderer2D::EndScene();
		m_Framebuffer->UnBind();
	}

	void RayTracerLayer::OnImGuiRender()
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


		ImGui::Begin("Viewport");
		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		//既没有Focused也没有Hovered的时候才会设置BlockEvents
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		//auto texture = m_Image->GetTextureRendererID();
		auto texture = m_Framebuffer->GetColorAttachment();
		ImVec2 viewport_size = ImGui::GetContentRegionAvail();
		if (viewport_size.x != m_Image->GetWidth() || viewport_size.y != m_Image->GetHeight())
		{
			m_Image->OnResize(viewport_size.x, viewport_size.y);
		}
		ImGui::Image((void*)texture, { viewport_size.x, viewport_size.y }, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();

		ImGui::End();
	}

	void RayTracerLayer::OnEvent(Event& e)
	{
		m_OrthographicCameraController.OnEvent(e);
	}
}