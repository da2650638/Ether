#include "etherpch.h"
#include "Scene.h"

#include "glm/glm.hpp"
#include "Components.h"
#include "Entity.h"

#include "Ether/Renderer/Renderer2D.h"

namespace Ether
{
	static void DoMath(const glm::mat4& transform)
	{

	}

	static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
	{

	}

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
		Camera* main_camera = nullptr;
		glm::mat4* camera_transform = nullptr;
		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view)
		{
			auto& [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
			if (camera.Primary)
			{
				main_camera = &camera.Camera;
				camera_transform = &transform.Transform;
				break;
			}
		}

		if (main_camera)
		{
			Renderer2D::BeginScene(*main_camera, *camera_transform);

			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				Renderer2D::DrawQuad(transform.Transform, sprite.Color);
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