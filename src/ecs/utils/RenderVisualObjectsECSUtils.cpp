#include "RenderVisualObjectsECSUtils.hpp"

#include <core/Application.hpp>
#include <core/RenderVisualObjects.hpp>

#include <ecs/ECSWorld.hpp>
#include <ecs/components/VisualObjectComponent.hpp>

#include "ECSFactoryObjects.hpp"

namespace ECS
{
    entt::entity RenderVisualObjectsECSUtils::createVisualObject(std::string_view assetId, int layerId,
        const sf::Vector2f& position, const sf::Vector2f& scale, float rotation)
    {
        return ECS::createVisualObject(assetId, layerId, position, scale, rotation);
    }

    void RenderVisualObjectsECSUtils::moveVisualObject(entt::entity entity, int newLayerId)
    {
        entt::registry& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        if (auto visualObjectComponent = registry.try_get<ECS::VisualObjectComponent>(entity)) {
            Core::Application::getInstance().getRenderVisualObjects()->moveVisualObject(visualObjectComponent->visualObjectPtr, newLayerId);
        }
    }

    void RenderVisualObjectsECSUtils::moveUpVisualObject(entt::entity entity)
    {
        entt::registry& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        if (auto visualObjectComponent = registry.try_get<ECS::VisualObjectComponent>(entity)) {
            Core::Application::getInstance().getRenderVisualObjects()->moveUpVisualObject(visualObjectComponent->visualObjectPtr);
        }
    }

    void RenderVisualObjectsECSUtils::moveDownVisualObject(entt::entity entity)
    {
        entt::registry& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        if (auto visualObjectComponent = registry.try_get<ECS::VisualObjectComponent>(entity)) {
            Core::Application::getInstance().getRenderVisualObjects()->moveDownVisualObject(visualObjectComponent->visualObjectPtr);
        }
    }

    void RenderVisualObjectsECSUtils::removeVisualObject(entt::entity entity)
    {
        entt::registry& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        if (auto visualObjectComponent = registry.try_get<ECS::VisualObjectComponent>(entity)) {
            Core::Application::getInstance().getRenderVisualObjects()->removeVisualObject(visualObjectComponent->visualObjectPtr);
            visualObjectComponent->visualObjectPtr.reset();
        }

        registry.destroy(entity);
    }
}
