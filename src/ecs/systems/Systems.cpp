#include "Systems.hpp"

#include <core/Application.hpp>

#include <ecs/ECSWorld.hpp>

namespace ECS
{
    void Systems::addSystem(SystemPtr&& systemPtr)
    {
        _systems.push_back(std::move(systemPtr));
    }

    void Systems::onUpdate(float deltaTime)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        for (auto& systemPtr : _systems) {
            systemPtr->onUpdate(deltaTime, registry);
        }
    }

    void Systems::onDraw(sf::RenderWindow* wndPtr)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        for (auto& systemPtr : _systems) {
            systemPtr->onDraw(registry, wndPtr);
        }
    }
}
