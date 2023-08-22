#include "SceneHierarchyPanel.h"

#include "imgui.h"
#include "imgui_internal.h"

#include <glm/gtc/type_ptr.hpp>

namespace Ether
{
	SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
	{
		SetContext(context);
	}

	void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
	{
		m_Context = context;
	}

	void SceneHierarchyPanel::OnImGuiRender()
	{
		//ImGui::ShowDemoWindow();

		ImGui::Begin("Scene Hierarchy");

		//Iterate everything in registry
		m_Context->m_Registry.each(
			[&](auto entity_id)
			{
				Entity entity{ entity_id, m_Context.get() };
				DrawEntityNode(entity);
			}
		);

		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		{
			m_SelectionContext = {};
		}

		if (ImGui::BeginPopupContextWindow("Scene Hierarchy Menu", 1/* 1代表右键 */, false))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
				m_Context->CreateEntity("Empty Entity");
			ImGui::EndPopup();
		}

		ImGui::End();

		ImGui::Begin("Properties");
		//If we select any entity in the scene then show its properties
		if (m_SelectionContext)
		{
			DrawComponents(m_SelectionContext);
		}
		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		//默认不打开树节点，因此也默认一开始也不需要使用到TreePop()函数
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0);
		bool opened = ImGui::TreeNodeEx( /*Unique Id*/(void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		bool entity_deleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete This Entity"))
				entity_deleted = true;
			ImGui::EndPopup();
		}

		if (opened)
		{
			ImGui::TreePop();
		}

		if (entity_deleted)
		{
			m_Context->DestroyEntity(entity);
			if (m_SelectionContext == entity)
				m_SelectionContext = {};
		}
	}

	static void DrawVec3Control(const std::string& label, glm::vec3& values, float reset_value = 0.0f, float column_width = 100.f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto bold_font = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, column_width);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0,0 });

		float line_height = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 button_size = { line_height + 3.0f, line_height };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(bold_font);
		if (ImGui::Button("X", button_size))
		{
			values.x = reset_value;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(bold_font);
		if (ImGui::Button("Y", button_size))
			values.y = reset_value;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(bold_font);
		if (ImGui::Button("Z", button_size))
			values.z = reset_value;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}

	template <typename T, typename UIFunction>
	static void DrawComponent(const std::string& name, Entity entity, UIFunction ui_function)
	{
		const ImGuiTreeNodeFlags tree_node_flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
		if (entity.HasComponent<T>())
		{
			auto& component = entity.GetComponent<T>();
			ImVec2 content_region_available = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float line_height = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();
			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), tree_node_flags, name.c_str());
			ImGui::PopStyleVar();
			ImGui::SameLine(content_region_available.x - line_height * 0.5f);
			if (ImGui::Button("+", ImVec2{ line_height, line_height }))
			{
				ImGui::OpenPopup("ComponentSettings");
			}

			bool remove_component = false;
			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove component"))
					remove_component = true;

				ImGui::EndPopup();
			}

			if (open)
			{
				ui_function(component);
				ImGui::TreePop();
			}

			if (remove_component)
				entity.RemoveComponent<T>();

		}
	}

	void SceneHierarchyPanel::DrawComponents(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			DrawComponent<TagComponent>("Tag", entity, 
				[&](auto& component) 
				{
					auto& tag = component.Tag;
					char buffer[256];
					memset(buffer, 0, sizeof(buffer));
					strcpy_s(buffer, tag.c_str());
					if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
					{
						tag = std::string(buffer);
					}
				}
			);
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-1);
		if (ImGui::Button("AddComponent"))
		{
			ImGui::OpenPopup("AddComponentPopup");
		}
		if (ImGui::BeginPopup("AddComponentPopup"))
		{
			if (ImGui::MenuItem("Camera"))
			{
				m_SelectionContext.AddComponent<CameraComponent>();
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("Sprite Renderer"))
			{
				m_SelectionContext.AddComponent<SpriteRendererComponent>();
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
		ImGui::PopItemWidth();

		if (entity.HasComponent<TransformComponent>())
		{
			DrawComponent<TransformComponent>("Transform", entity, 
				[&](auto& component) 
				{
					auto& tc = component;
					DrawVec3Control("Translation", tc.Translation, 0.0f);
					glm::vec3 rotation = glm::degrees(tc.Rotation);
					DrawVec3Control("Rotation", rotation, 0.0f);
					tc.Rotation = glm::radians(rotation);
					DrawVec3Control("Scale", tc.Scale, 1.0f);
				}
			);
		}

		if (entity.HasComponent<CameraComponent>())
		{
			DrawComponent<CameraComponent>("Camera", entity, 
				[&](auto& component)
				{
					auto& camera_component = component;
					auto& camera = camera_component.Camera;

					const char* projection_type_strings[] = { "Perspective", "Orthographic" };
					const char* current_projection_type_string = projection_type_strings[(int)camera_component.Camera.GetProjectionType()];
					bool& parimary_camera = component.Primary;
					ImGui::Checkbox("Primary Camera", &parimary_camera);
					if (parimary_camera)
					{
						//所有的相机的Primary都设置成false
						m_Context->m_Registry.view<CameraComponent>().each(
							[=](entt::entity entity_id, auto& camera_component)
							{
								camera_component.Primary = false;
							}
						);
						//并且只设置当前相机的Primary为true
						component.Primary = true;
					}
					
					if (ImGui::BeginCombo("Projection", current_projection_type_string))
					{
						for (int i = 0; i < 2; i++)
						{
							bool is_selected = (current_projection_type_string == projection_type_strings[i]);
							if (ImGui::Selectable(projection_type_strings[i], is_selected))	//这个if语句就代表鼠标点击到某个Combo选项上了，不点击的话，括号里面的代码不会执行
							{
								current_projection_type_string = projection_type_strings[i];
								camera_component.Camera.SetProjectionType((SceneCamera::ProjectionType)i);
							}

							//不明白这段代码的意思，是否有这段代码不影响程序正常运行
							if (is_selected)
							{
								ImGui::SetItemDefaultFocus();
							}
						}

						ImGui::EndCombo();
					}

					if (camera_component.Camera.GetProjectionType() == SceneCamera::ProjectionType::Perspective)
					{
						float perspective_vertical_fov = glm::degrees(camera.GetPerspectiveVerticalFOV());
						if (ImGui::DragFloat("Vertical FOV", &perspective_vertical_fov))
						{
							camera.SetPerspectiveVerticalFOV(glm::radians(perspective_vertical_fov));
						}

						float perspective_nearclip = camera.GetPerspectiveNearClip();
						if (ImGui::DragFloat("Near", &perspective_nearclip))
						{
							camera.SetPerspectiveNearClip(perspective_nearclip);
						}

						float perspective_farclip = camera.GetPerspectiveFarClip();
						if (ImGui::DragFloat("Far", &perspective_farclip))
						{
							camera.SetPerspectiveFarClip(perspective_farclip);
						}
					}

					if (camera_component.Camera.GetProjectionType() == SceneCamera::ProjectionType::Orthographic)
					{
						float orthographic_size = camera.GetOrthographicSize();
						if (ImGui::DragFloat("Size", &orthographic_size))
						{
							camera.SetOrthographicSize(orthographic_size);
						}

						float orthographic_nearclip = camera.GetOrthographicNearClip();
						if (ImGui::DragFloat("Near", &orthographic_nearclip))
						{
							camera.SetOrthographicNearClip(orthographic_nearclip);
						}

						float orthographic_farclip = camera.GetOrthographicFarClip();
						if (ImGui::DragFloat("Far", &orthographic_farclip))
						{
							camera.SetOrthographicFarClip(orthographic_farclip);
						}
					}
				}
			);
		}
	
		if (entity.HasComponent<SpriteRendererComponent>())
		{
			DrawComponent<SpriteRendererComponent>("Sprite Renderer", entity, 
				[&](auto& component)
				{
					ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
				}
			);
		}
	}
}