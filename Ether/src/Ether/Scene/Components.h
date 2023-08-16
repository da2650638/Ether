#pragma once

#include "Ether/Scene/SceneCamera.h"

#include <glm/glm.hpp>
#include <string>

namespace Ether
{
	struct TagComponent
	{
		std::string Tag = "Entity";

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

	struct TransformComponent
	{
		glm::mat4 Transform = glm::mat4(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform) { }

		//×ªÐÍÔËËã·û
		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color = glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent& other) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) {}
	};

	struct CameraComponent
	{
		Ether::SceneCamera Camera;
		//Basiclly it's possible to have multiple cameras in the scene, and you may want to switch between them.
		bool Primary = true; //TODO: think about moving to scene.
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent& other) = default;
	};
}