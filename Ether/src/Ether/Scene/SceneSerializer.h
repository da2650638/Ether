#pragma once

#include "Scene.h"

#include <yaml-cpp/yaml.h>

namespace Ether
{
	class SceneSerializer
	{
	public:
		SceneSerializer() = default;
		SceneSerializer(const Ref<Scene>& scene)
			: m_Scene(scene) {}

		void Serialize(const std::string& filepath);
		void SerializeRuntime(const std::string& filepath);

		bool Deserialize(const std::string& filepath);
		bool DeserializeRuntime(const std::string& filepaths);


		static void SerializeEntity(YAML::Emitter& out, Entity entity);
	private:
		Ref<Scene> m_Scene;
	};
}