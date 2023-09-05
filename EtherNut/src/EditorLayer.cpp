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

		m_Scene = std::make_shared<Scene>();

		//auto square = m_Scene->CreateEntity("Green Square");
		//square.AddComponent<SpriteRendererComponent>(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		//auto square2 = m_Scene->CreateEntity("Red Square");
		//square2.AddComponent<SpriteRendererComponent>(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

		//m_SquareEntity = square;
		//m_SquareEntity2 = square2;
		//m_CameraEntity = m_Scene->CreateEntity("CameraEntity");
		//m_CameraEntity.AddComponent<CameraComponent>();

		m_SceneHierarchyPanel.SetContext(m_Scene);

		//struct CameraController : public ScriptableEntity
		//{
		//	virtual void OnCreate() override
		//	{
		//		ETHER_CORE_INFO("CameraController::OnCreate");
		//	}

		//	virtual void OnDestroy() override
		//	{

		//	}

		//	virtual void OnUpdate(Timestep ts) override
		//	{
		//		ETHER_PROFILE_FUNCTION();

		//		auto& transform_component = GetComponent<TransformComponent>();

		//		if (Input::IsKeyPressed(ETHER_KEY_W))
		//		{
		//			transform_component.Translation.y += std::cos(glm::radians(transform_component.Rotation.z)) * ts * m_CameraTranslationSpeed;
		//			transform_component.Translation.x -= std::sin(glm::radians(transform_component.Rotation.z)) * ts * m_CameraTranslationSpeed;
		//		}
		//		if (Input::IsKeyPressed(ETHER_KEY_S))
		//		{
		//			transform_component.Translation.y -= std::cos(glm::radians(transform_component.Rotation.z)) * ts * m_CameraTranslationSpeed;
		//			transform_component.Translation.x += std::sin(glm::radians(transform_component.Rotation.z)) * ts * m_CameraTranslationSpeed;
		//		}
		//		if (Input::IsKeyPressed(ETHER_KEY_A))
		//		{
		//			transform_component.Translation.x -= std::cos(glm::radians(transform_component.Rotation.z)) * ts * m_CameraTranslationSpeed;
		//			transform_component.Translation.y -= std::sin(glm::radians(transform_component.Rotation.z)) * ts * m_CameraTranslationSpeed;
		//		}
		//		if (Input::IsKeyPressed(ETHER_KEY_D))
		//		{
		//			transform_component.Translation.x += std::cos(glm::radians(transform_component.Rotation.z)) * ts * m_CameraTranslationSpeed;
		//			transform_component.Translation.y += std::sin(glm::radians(transform_component.Rotation.z)) * ts * m_CameraTranslationSpeed;
		//		}

		//		if (Input::IsKeyPressed(ETHER_KEY_UP))
		//		{
		//			transform_component.Translation.z -= ts * m_CameraTranslationSpeed;
		//		}
		//		if (Input::IsKeyPressed(ETHER_KEY_DOWN))
		//		{
		//			transform_component.Translation.z += ts * m_CameraTranslationSpeed;
		//		}

		//		if (m_Rotation)
		//		{
		//			if (Input::IsKeyPressed(ETHER_KEY_Q))
		//			{
		//				transform_component.Rotation.z += ts * m_CameraRotationSpeed;
		//			}
		//			if (Input::IsKeyPressed(ETHER_KEY_E))
		//			{
		//				transform_component.Rotation.z -= ts * m_CameraRotationSpeed;
		//			}
		//			if (transform_component.Rotation.z > 180.0f)
		//			{
		//				transform_component.Rotation.z -= 360.0f;
		//			}
		//			if (transform_component.Rotation.z < -180.0f)
		//			{
		//				transform_component.Rotation.z += 360.0f;
		//			}
		//		}
		//	}

		//	bool m_Rotation = true;

		//	float m_CameraTranslationSpeed = 4.5f;
		//	float m_CameraRotationSpeed = 30.0f;
		//};

		//m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
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
			if(m_ViewportFocused)
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

			ETHER_PROFILE_SCOPE("Renderer Draw");

			m_Scene->OnUpdate(ts);

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
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
				//ImGui::MenuItem("Padding", NULL, &opt_padding);
				//ImGui::Separator();

				if (ImGui::MenuItem("New", "Ctrl+N"))
					NewScene();
				if (ImGui::MenuItem("Open...", "Ctrl+O"))
					OpenScene();
				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
					SaveSceneAs();
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

		m_SceneHierarchyPanel.OnImGuiRender();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
		ImGui::Begin("Viewport");
		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		//既没有Focused也没有Hovered的时候才会设置BlockEvents
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

		auto texture = m_Framebuffer->GetColorAttachment();
		ImVec2 viewport_size_now = ImGui::GetContentRegionAvail();
		m_ViewportWidth = viewport_size_now.x;
		m_ViewportHeight = viewport_size_now.y;
		ImVec2 framebuffer_size_now = { (float)m_Framebuffer->GetFramebufferSpecification().Width, (float)m_Framebuffer->GetFramebufferSpecification().Height };
		if (framebuffer_size_now.x != viewport_size_now.x || framebuffer_size_now.y != viewport_size_now.y)
		{
			m_Framebuffer->Resize((uint32_t)viewport_size_now.x, (uint32_t)viewport_size_now.y);
			m_OrthographicCameraController.OnResize((uint32_t)viewport_size_now.x, (uint32_t)viewport_size_now.y);
		
			m_Scene->OnViewportResize((uint32_t)viewport_size_now.x, (uint32_t)viewport_size_now.y);
		}
		ImGui::Image((void*)texture, { viewport_size_now.x, viewport_size_now.y }, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		m_OrthographicCameraController.OnEvent(e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(ETHER_BIND_EVENT_FN(OnKeyPressed));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		bool control = Input::IsKeyPressed(ETHER_KEY_LEFT_CONTROL) || Input::IsKeyPressed(ETHER_KEY_RIGHT_CONTROL);
		bool shift = Input::IsKeyPressed(ETHER_KEY_LEFT_SHIFT) || Input::IsKeyPressed(ETHER_KEY_RIGHT_SHIFT);
		switch (e.GetKeyCode())
		{
			case Key::N:
			{
				if (control)
				{
					NewScene();
				}
				break;
			}
			case Key::O:
			{
				if (control)
				{
					OpenScene();
				}
				break;
			}
			case Key::S:
			{
				if (control && shift)
				{
					SaveSceneAs();
				}
				break;
			}
		}
		return false;
	}

	void EditorLayer::NewScene()
	{
		m_Scene = std::make_shared<Scene>();
		m_Scene->OnViewportResize(m_ViewportWidth, m_ViewportHeight);
		m_SceneHierarchyPanel.SetContext(m_Scene);
	}

	void EditorLayer::OpenScene()
	{
		std::optional<std::string> filepath = FileDialogs::OpenFile("Scene(*.scene)\0*.scene\0");
		if (filepath)
		{
			m_Scene = std::make_shared<Scene>();
			m_Scene->OnViewportResize(m_ViewportWidth, m_ViewportHeight);
			m_SceneHierarchyPanel.SetContext(m_Scene);

			SceneSerializer serializer(m_Scene);
			serializer.Deserialize(filepath.value());
		}
	}

	void EditorLayer::SaveSceneAs()
	{
		std::optional<std::string> filepath = FileDialogs::SaveFile("Scene (*.scene)\0*.scene\0");
		if (filepath)
		{
			SceneSerializer serializer(m_Scene);
			serializer.Serialize(filepath.value());
		}
	}

}
