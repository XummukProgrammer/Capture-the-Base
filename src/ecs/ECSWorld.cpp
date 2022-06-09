#include "ECSWorld.hpp"

namespace ECS
{
    void World::create()
    {
        _systemsPtr = new Systems;
    }

    void World::destroy()
    {
        delete _systemsPtr;
    }

    entt::registry& World::getRegistry()
    {
        return _registry;
    }

    void World::onUpdate(float deltaTime)
    {
        _systemsPtr->onUpdate(deltaTime);
    }
}
