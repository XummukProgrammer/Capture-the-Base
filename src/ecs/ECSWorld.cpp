#include "ECSWorld.hpp"

namespace ECS
{
    entt::registry& World::getRegistry()
    {
        return _registry;
    }
}
