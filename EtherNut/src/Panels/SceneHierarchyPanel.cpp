#include "SceneHierarchyPanel.h"

#include "imgui.h"

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

		ImGui::End();

		ImGui::Begin("Properties");
		//If we select any entity in the scene then show its properties
		if (m_SelectionContext)
			DrawComponent(m_SelectionContext);
		ImGui::End();
	}

	void SceneHierarchyPanel::DrawEntityNode(Entity entity)
	{
		auto& tag = entity.GetComponent<TagComponent>().Tag;

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0);
		bool opened = ImGui::TreeNodeEx( /*Unique Id*/(void*)(uint64_t)(uint32_t)entity, flags, tag.c_str());
		if (ImGui::IsItemClicked())
		{
			m_SelectionContext = entity;
		}

		if (opened)
		{
			ImGui::TreePop();
		}
	}

	void SceneHierarchyPanel::DrawComponent(Entity entity)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tag = entity.GetComponent<TagComponent>().Tag;
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			strcpy_s(buffer, tag.c_str());
			if (ImGui::InputText("Tag", buffer, sizeof(buffer)))
			{
				tag = std::string(buffer);
			}
		}

		if (entity.HasComponent<TransformComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(TransformComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
			{
				auto& transform = entity.GetComponent<TransformComponent>().Transform;
				ImGui::DragFloat3("Position", glm::value_ptr(transform[3]), 0.1f);
				ImGui::TreePop();
			}
		}

		if (entity.HasComponent<CameraComponent>())
		{
			if (ImGui::TreeNodeEx((void*)typeid(CameraComponent).hash_code(), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
			{
				auto& camera_component = entity.GetComponent<CameraComponent>();
				auto& camera = camera_component.Camera;

				const char* projection_type_strings[] = { "Perspective", "Orthographic" };
				const char* current_projection_type_string = projection_type_strings[(int)camera_component.Camera.GetProjectionType()];
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


				ImGui::TreePop();
			}
		}
	}
}