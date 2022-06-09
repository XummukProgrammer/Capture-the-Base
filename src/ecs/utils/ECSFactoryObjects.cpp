#include "ECSFactoryObjects.hpp"

#include <core/Application.hpp>
#include <core/RenderVisualObjects.hpp>

#include <ecs/ECSWorld.hpp>
#include <ecs/components/VisualObjectComponent.hpp>

namespace ECS
{
    entt::entity createVisualObject(std::string_view assetId, int layerId)
    {
        entt::registry& registry = Core::Application::getInstance().getECSWorld()->getRegistry();
        entt::entity entity = registry.create();

        ECS::VisualObjectComponent& visualObjectComponent = registry.emplace<ECS::VisualObjectComponent>(entity);
        visualObjectComponent.visualObjectPtr = std::make_shared<Core::VisualObject>();
        visualObjectComponent.visualObjectPtr->loadFromAsset(assetId);
        Core::Application::getInstance().getRenderVisualObjects()->addVisualObject(visualObjectComponent.visualObjectPtr, layerId);

        return entity;
    }
}
