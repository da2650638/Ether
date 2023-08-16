#pragma once

#include "Scene.h"

#include "entt.hpp"

namespace Ether
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			ETHER_CORE_ASSERT(!HasComponent<T>(), "Entity already have component!");
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template <typename T>
		T& GetComponent()
		{
			ETHER_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template <typename T>
		void RemoveComponent()
		{
			ETHER_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		template <typename T>
		bool HasComponent()
		{
			//all_of function can do the same as old has function
			return m_Scene->m_Registry.all_of<T>(m_EntityHandle);
		}
		operator bool() const { return m_EntityHandle != entt::null; }
	private:
		entt::entity m_EntityHandle{ entt::null };
		//TODO: need optimizing.We must using our own weak_ptr to wrapper this ptr.
		Scene* m_Scene;
	};
}