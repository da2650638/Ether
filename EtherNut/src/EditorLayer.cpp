#include "EditorLayer.h"

#include "imgui.h"

#include <ImGuizmo.h>

#include <glm/gtx/string_cast.hpp>

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
		spec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
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
		m_EditorCamera = EditorCamera(30.f, 1.778, 0.1f, 1000.f);

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
			m_EditorCamera.OnUpdate(ts);
		}

		{
			ETHER_PROFILE_SCOPE("Renderer Prep");
			m_Framebuffer->Bind();
			Renderer::Clear();
			Renderer::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });

			m_Framebuffer->ClearAttachment(1, - 1);

			Renderer2D::ResetStats();
		}

		{

			ETHER_PROFILE_SCOPE("Renderer Draw");

			m_Scene->OnUpdateEditor(ts, m_EditorCamera);

			auto mouse_pos = ImGui::GetMousePos();	//获取鼠标的坐标（整个屏幕范围）
			float mouse_x = mouse_pos.x, mouse_y = mouse_pos.y;
			mouse_x -= m_ViewportBounds[0].x, mouse_y -= m_ViewportBounds[0].y;
			//上下翻转
			mouse_y = (m_ViewportBounds[1].y - m_ViewportBounds[0].y) - mouse_y;
			int mx = (int)mouse_x, my = (int)mouse_y;
			glm::vec2 viewport_size = m_ViewportBounds[1] - m_ViewportBounds[0];
			if (mx >= 0 && my >= 0 && mx < (int)(viewport_size.x) && my < (int)(viewport_size.y))
			{
				int entity_id = m_Framebuffer->ReadPixel(1, mx, my);
				ETHER_CORE_INFO("Entity ID(place holder): {0}", entity_id);
			}

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
		ImGui::Text("Renderer Stats:");
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::Separator();
		const ImGuiTreeNodeFlags tree_node_flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_FramePadding;
		//const ImGuiTreeNodeFlags tree_node_flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		ImGui::Text("Editor Camera:");
		bool open = ImGui::TreeNodeEx("Cursor Position:", tree_node_flags, "Cursor Position:");
		if (open)
		{
			ImGui::Text("x: %.3f", m_EditorCamera.m_InitialMousePosition.x);
			ImGui::Text("y: %.3f", m_EditorCamera.m_InitialMousePosition.y);
			ImGui::TreePop();
		}
		open = ImGui::TreeNodeEx("Viewport Size:", tree_node_flags, "Viewport Size:");
		if (open)
		{
			ImGui::Text("Width: %.3f", m_EditorCamera.m_ViewportWidth);
			ImGui::Text("Height: %.3f", m_EditorCamera.m_ViewportHeight);
			ImGui::TreePop();
		}
		open = ImGui::TreeNodeEx("Directions:", tree_node_flags, "Directions:");
		if (open)
		{
			ImGui::Text("Forward: %s", glm::to_string(m_EditorCamera.GetForwardDirection()).c_str());
			ImGui::Text("Up: %s", glm::to_string(m_EditorCamera.GetUpDirection()).c_str());
			ImGui::Text("Right: %s", glm::to_string(m_EditorCamera.GetRightDirection()).c_str());
			ImGui::TreePop();
		}
		open = ImGui::TreeNodeEx("Perspective:", tree_node_flags, "Perspective:");
		if (open)
		{
			ImGui::Text("FOV: %.3f", m_EditorCamera.m_FOV);
			ImGui::Text("AspectRatio: %.3f", m_EditorCamera.m_AspectRatio);
			ImGui::Text("NearClip: %.3f", m_EditorCamera.m_NearClip);
			ImGui::Text("FarClip: %.3f", m_EditorCamera.m_FarClip);
			ImGui::TreePop();
		}
		open = ImGui::TreeNodeEx("Rotation:", tree_node_flags, "Rotation:");
		if (open)
		{
			ImGui::Text("Pitch(degrees): %.3f", glm::degrees(m_EditorCamera.m_Pitch));
			ImGui::Text("Yaw(degrees): %.3f", glm::degrees(m_EditorCamera.m_Yaw));
			ImGui::TreePop();
		}
		open = ImGui::TreeNodeEx("Translate:", tree_node_flags, "Translate:");
		if (open)
		{
			ImGui::Text("Position: %.3f, %.3f, %.3f", m_EditorCamera.m_Position.x, m_EditorCamera.m_Position.y, m_EditorCamera.m_Position.z);
			ImGui::Text("FocalPoint: %.3f, %.3f, %.3f", m_EditorCamera.m_FocalPoint.x, m_EditorCamera.m_FocalPoint.y, m_EditorCamera.m_FocalPoint.z);
			ImGui::Text("Distance: %.3f", m_EditorCamera.m_Distance);
			ImGui::TreePop();
		}
		//glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };

		ImGui::End();

		m_SceneHierarchyPanel.OnImGuiRender();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });
		ImGui::Begin("Viewport");
		
		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		//既没有Focused也没有Hovered的时候才会设置BlockEvents
		Application::Get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);
		
		ImVec2 min_bound = ImGui::GetWindowContentRegionMin();
		ImVec2 max_bound = ImGui::GetWindowContentRegionMax();
		ImVec2 window_pos = ImGui::GetWindowPos();	//返回的是窗口的左上角在整个屏幕中的坐标
		min_bound.x += window_pos.x;
		min_bound.y += window_pos.y;
		max_bound.x += window_pos.x;
		max_bound.y += window_pos.y;
		m_ViewportBounds[0] = { min_bound.x, min_bound.y };
		m_ViewportBounds[1] = { max_bound.x, max_bound.y };

		auto texture = m_Framebuffer->GetColorAttachment(0);
		ImVec2 viewport_size_now = ImGui::GetContentRegionAvail();
		m_ViewportWidth = viewport_size_now.x;
		m_ViewportHeight = viewport_size_now.y;
		ImVec2 framebuffer_size_now = { (float)m_Framebuffer->GetFramebufferSpecification().Width, (float)m_Framebuffer->GetFramebufferSpecification().Height };
		if (framebuffer_size_now.x != viewport_size_now.x || framebuffer_size_now.y != viewport_size_now.y)
		{
			m_Framebuffer->Resize((uint32_t)viewport_size_now.x, (uint32_t)viewport_size_now.y);
			m_OrthographicCameraController.OnResize((uint32_t)viewport_size_now.x, (uint32_t)viewport_size_now.y);
		
			m_EditorCamera.SetViewportSize(viewport_size_now.x, viewport_size_now.y);
			m_Scene->OnViewportResize((uint32_t)viewport_size_now.x, (uint32_t)viewport_size_now.y);
		}
		ImGui::Image((void*)texture, { viewport_size_now.x, viewport_size_now.y }, ImVec2(0, 1), ImVec2(1, 0));

		//ImGuizmo
		Entity entity = m_SceneHierarchyPanel.GetSelectionContext();
		if (entity)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();

			ImGuizmo::SetRect(min_bound.x, min_bound.y, max_bound.x - min_bound.x, max_bound.y - min_bound.y);

			//Entity runtime_camera_entity = m_Scene->GetPrimaryCameraEntity();
			if (/*runtime_camera_entity && */m_GizmoType != -1)
			{

				//glm::mat4 camera_view = glm::inverse(camera_entity.GetComponent<TransformComponent>().GetTransform());
				//glm::mat4 camera_projection = camera_entity.GetComponent<CameraComponent>().Camera.GetProjection();
				//glm::mat4 transform = entity.GetComponent<TransformComponent>().GetTransform();
				//ImGuizmo::Manipulate(glm::value_ptr(camera_view), glm::value_ptr(camera_projection), (ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform));
				glm::mat4 camera_view = m_EditorCamera.GetViewMatrix();
				glm::mat4 camera_projection = m_EditorCamera.GetProjection();
				glm::mat4 transform = entity.GetComponent<TransformComponent>().GetTransform();
				ImGuizmo::Manipulate(glm::value_ptr(camera_view), glm::value_ptr(camera_projection), (ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform));

				if (ImGuizmo::IsUsing())
				{
					glm::vec3 translation, rotation, scale;
					Math::DecomposeTransform(transform, translation, rotation, scale);

					auto& entity_transform_component = entity.GetComponent<TransformComponent>();
					if (m_GizmoType == ImGuizmo::OPERATION::TRANSLATE)
					{
						entity_transform_component.Translation = translation;
					}
					if (m_GizmoType == ImGuizmo::OPERATION::SCALE)
					{
						entity_transform_component.Scale = scale;
					}
					if (m_GizmoType == ImGuizmo::OPERATION::ROTATE)
					{
						glm::vec3 delta_rotation = rotation - entity_transform_component.Rotation;
						entity_transform_component.Rotation += delta_rotation;
					}					
				}
			}
		}

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		//m_OrthographicCameraController.OnEvent(e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(ETHER_BIND_EVENT_FN(OnKeyPressed));
		m_EditorCamera.OnEvent(e);
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
			// Gizmos
			case Key::Q:
			{
				if (!ImGuizmo::IsUsing())
					m_GizmoType = - 1;
				break;
			}
			case Key::W:
			{
				if (!ImGuizmo::IsUsing())
					m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
				break;
			}
			case Key::E:
			{
				if (!ImGuizmo::IsUsing())
					m_GizmoType = ImGuizmo::OPERATION::ROTATE;
				break;
			}
			case Key::R:
			{
				if (!ImGuizmo::IsUsing())
					m_GizmoType = ImGuizmo::OPERATION::SCALE;
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
