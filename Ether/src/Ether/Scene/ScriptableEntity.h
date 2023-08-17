#pragma once

#include "Entity.h"
#include "Ether/Core/Timestep.h"

namespace Ether
{
	class Scene;
	class ScriptableEntity
	{
	public:
		ScriptableEntity() = default;
		ScriptableEntity(entt::entity handle, Scene* scene)
			: m_Entity(handle, scene) {}
		virtual ~ScriptableEntity() {}

		template <typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
	protected:
		virtual void OnCreate() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnDestroy() {}
	private:
		Entity m_Entity;
		friend class Scene;
	};
}