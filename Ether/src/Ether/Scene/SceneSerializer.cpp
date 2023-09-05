#include "etherpch.h"
#include "SceneSerializer.h"

#include "Entity.h"
#include "Components.h"

namespace YAML
{
	//TODO: read the relate yaml codes. 
	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
}

namespace Ether
{
	YAML::Emitter& operator<<(YAML::Emitter& out,const glm::vec3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	void SceneSerializer::SerializeEntity(YAML::Emitter& out, Entity entity)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Entity" << YAML::Value << "12837192831273"; //TODO: There should be the entity uuid.
		if (entity.HasComponent<TagComponent>())
		{
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap; //TagComponent
			auto& component = entity.GetComponent<TagComponent>();
			out << YAML::Key << "Tag" << YAML::Value << component.Tag;
			out << YAML::EndMap; //TagComponent
		}

		if (entity.HasComponent<TransformComponent>())
		{
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap; //TransformComponent
			auto& component = entity.GetComponent<TransformComponent>();
			out << YAML::Key << "Translation" << YAML::Value << component.Translation;
			out << YAML::Key << "Rotation" << YAML::Value << component.Rotation;
			out << YAML::Key << "Scale" << YAML::Value << component.Scale;
			out << YAML::EndMap; //TransformComponent
		}

		if (entity.HasComponent<CameraComponent>())
		{
			out << YAML::Key << "CameraComponent";
			out << YAML::BeginMap; //CameraComponent
			auto& component = entity.GetComponent<CameraComponent>();
			auto& camera = component.Camera;
			out << YAML::Key << "Camera" << YAML::Value;
			out << YAML::BeginMap; //Camera
			out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.GetProjectionType();
			out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.GetPerspectiveVerticalFOV();
			out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.GetPerspectiveNearClip();
			out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.GetPerspectiveFarClip();
			out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthographicSize();
			out << YAML::Key << "OrthographicNear" << YAML::Value << camera.GetOrthographicNearClip();
			out << YAML::Key << "OrthographicFar" << YAML::Value << camera.GetOrthographicFarClip();
			out << YAML::EndMap; //Camera
			out << YAML::Key << "Primary" << YAML::Value << component.Primary;
			out << YAML::Key << "FixedAspectRatio" << YAML::Value << component.FixedAspectRatio;
			out << YAML::EndMap; //CameraComponent
		}

		if (entity.HasComponent<SpriteRendererComponent>())
		{
			out << YAML::Key << "SpriteRendererComponent";
			out << YAML::BeginMap; // SpriteRendererComponent

			auto& spriteRendererComponent = entity.GetComponent<SpriteRendererComponent>();
			out << YAML::Key << "Color" << YAML::Value << spriteRendererComponent.Color;

			out << YAML::EndMap; // SpriteRendererComponent
		}

		out << YAML::EndMap;
	}

	void SceneSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Untitled Scene";
		out << YAML::Key << "Entities" << YAML::Value;
		out << YAML::BeginSeq;
		m_Scene->m_Registry.each(
			[&](auto entityID) 
			{
				Entity entity = { entityID, m_Scene.get() };
				if (!entity)
					return;
				SerializeEntity(out, entity);
			}
		);
		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream ofs(filepath);
		ofs << out.c_str();
		ofs.flush();
		ofs.close();
	}

	void SceneSerializer::SerializeRuntime(const std::string& filepath)
	{
		ETHER_CORE_ASSERT(false, "SerializeRuntime Is Not A Implemented Function. Please Do Not Use It.");
	}

	bool SceneSerializer::Deserialize(const std::string& filepath)
	{
		//std::ifstream ifs(filepath);
		//std::stringstream ss;
		//ss << ifs.rdbuf();
		//YAML::Node data = YAML::Load(ss.str());
		//Use YAML::LoadFile instead of old way
		YAML::Node data = YAML::LoadFile(filepath);
		if (!data["Scene"])
			return false;

		std::string scene_name = data["Scene"].as<std::string>();
		ETHER_CORE_TRACE("Deserializing scene {0}...", scene_name);

		auto entities = data["Entities"];
		if (entities)
		{
			for (auto entity : entities)
			{
				uint64_t uuid = entity["Entity"].as<uint64_t>();	//TODO: implement the real uuid.
				
				std::string name;
				auto tag_component = entity["TagComponent"];
				if (tag_component)
					name = tag_component["Tag"].as<std::string>();

				Entity deserialized_entity = m_Scene->CreateEntity(name);

				glm::vec3 translation, rotation, scale;
				auto transform_component = entity["TransformComponent"];
				if (transform_component)
				{
					translation = transform_component["Translation"].as<glm::vec3>();
					rotation = transform_component["Rotation"].as<glm::vec3>();
					scale = transform_component["Scale"].as<glm::vec3>();
					deserialized_entity.GetComponent<TransformComponent>().Translation = translation;
					deserialized_entity.GetComponent<TransformComponent>().Rotation = rotation;
					deserialized_entity.GetComponent<TransformComponent>().Scale = scale;
				}

				SceneCamera camera;
				bool primary, fixed_aspect_ratio;
				auto camera_component = entity["CameraComponent"];
				if (camera_component)
				{
					auto c = camera_component["Camera"];
					if (c)
					{
						camera.SetProjectionType((SceneCamera::ProjectionType)c["ProjectionType"].as<int>());
						camera.SetPerspectiveVerticalFOV(c["PerspectiveFOV"].as<float>());
						camera.SetPerspectiveNearClip(c["PerspectiveNear"].as<float>());
						camera.SetPerspectiveFarClip(c["PerspectiveFar"].as<float>());
						camera.SetOrthographicSize(c["OrthographicSize"].as<float>());
						camera.SetOrthographicNearClip(c["OrthographicNear"].as<float>());
						camera.SetOrthographicFarClip(c["OrthographicFar"].as<float>());
					}
					primary = camera_component["Primary"].as<bool>();
					fixed_aspect_ratio = camera_component["FixedAspectRatio"].as<bool>();
					CameraComponent temp_camera_component;
					temp_camera_component.Camera = camera;
					temp_camera_component.Primary = primary;
					temp_camera_component.FixedAspectRatio = fixed_aspect_ratio;
					deserialized_entity.AddComponent<CameraComponent>(temp_camera_component);
				}

				glm::vec4 color;
				auto sprite_component = entity["SpriteRendererComponent"];
				if (sprite_component)
				{
					color = sprite_component["Color"].as<glm::vec4>();
					deserialized_entity.AddComponent<SpriteRendererComponent>(color);
				}
			}
		}

		return true;
	}

	bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
	{
		ETHER_CORE_ASSERT(false, "DeserializeRuntime Is Not A Implemented Function. Please Do Not Use It.");
		return false;
	}
}