#include "etherpch.h"
#include "Entity.h"

namespace Ether
{
    Entity::Entity(entt::entity handle, Scene* scene)
        : m_EntityHandle(handle), m_Scene(scene)
    {

    }
}
