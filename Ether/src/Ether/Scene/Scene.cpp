#include "etherpch.h"
#include "Scene.h"

#include "glm/glm.hpp"
#include "Components.h"
#include "Entity.h"

#include "Ether/Renderer/Renderer2D.h"
#include "Ether/Scene/ScriptableEntity.h"

namespace Ether
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity{ m_Registry.create(), this};
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>(name);
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		//Update Scripts
		m_Registry.view<NativeScriptComponent>().each(
			[=](entt::entity entity, NativeScriptComponent& nsc)
			{
				//如果Instance还没有被实例化，则需要进行实例化
				if (!nsc.Instance)
				{
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_Entity = { entity, this };
					nsc.Instance->OnCreate();
				}

				nsc.Instance->OnUpdate(ts);
			}
		);

		Camera* main_camera = nullptr;
		glm::mat4 camera_transform;
		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view)
		{
			auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
			if (camera.Primary)
			{
				main_camera = &camera.Camera;
				camera_transform = transform.GetTransform();
				break;
			}
		}

		if (main_camera)
		{
			Renderer2D::BeginScene(*main_camera, camera_transform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
			}

			Renderer2D::EndScene();
		}
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		//Resize our non-fixedAspectRatio cameras.
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& camera_component = view.get<CameraComponent>(entity);
			if (!camera_component.FixedAspectRatio)
			{
				camera_component.Camera.SetViewportSize(width, height);
			}
		}
	}
}