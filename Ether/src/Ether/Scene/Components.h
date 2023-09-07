#pragma once

#include "Ether/Scene/SceneCamera.h"
#include "ScriptableEntity.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

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
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };	//三个分量分别代表绕x,y,z三个轴旋转的角度
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) { }
		TransformComponent(const glm::vec3& translation, const glm::vec3& rotation, const glm::vec3& scale)
			: Translation(translation), Rotation(rotation), Scale(scale) {}

		glm::mat4 GetTransform() const
		{
			//旋转矩阵
			/*glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), Rotation.x, { 1.0f, 0.0f, 0.0f })
				* glm::rotate(glm::mat4(1.0f), Rotation.y, { 0.0f, 1.0f, 0.0f })
				* glm::rotate(glm::mat4(1.0f), Rotation.z, { 0.0f ,0.0f, 1.0f });

			glm::mat4 translate = glm::translate(glm::mat4(1.0f), Translation);
			
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), Scale);
			return translate * rotation * scale;*/
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}

		//转型运算符
		operator glm::mat4& () { return GetTransform(); }
		operator const glm::mat4& () const { return GetTransform(); }
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
		bool Primary = false; //TODO: think about moving to scene.
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent& other) = default;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance;

		ScriptableEntity* (*InstantiateScript)();
		void(*DestroyScript)(NativeScriptComponent* nsc);

		template <typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}

		NativeScriptComponent() = default;
		NativeScriptComponent(const NativeScriptComponent& other) = default;
	};
}