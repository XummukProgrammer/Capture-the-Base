#include "RenderVisualObjectsECSUtils.hpp"

#include <core/Application.hpp>
#include <core/RenderVisualObjects.hpp>

#include <ecs/ECSWorld.hpp>
#include <ecs/components/TransformComponent.hpp>
#include <ecs/components/VisualObjectComponent.hpp>

namespace ECS
{
    entt::entity RenderVisualObjectsECSUtils::createVisualObject(const VisualObjectCreateInfo& info)
    {
        entt::registry& registry = Core::Application::getInstance().getECSWorld()->getRegistry();
        entt::entity entity = registry.create();

        ECS::TransformComponent& transformComponent = registry.emplace<ECS::TransformComponent>(entity);
        transformComponent.position = info.position;
        transformComponent.scale = info.scale;
        transformComponent.rotation = info.rotation;

        // Load Visual Object
        ECS::VisualObjectComponent& visualObjectComponent = registry.emplace<ECS::VisualObjectComponent>(entity);
        
        auto visualObject = std::make_shared<Core::VisualObject>();
        visualObject->loadFromAsset(info.assetId);
        
        auto& sprite = visualObject->getSprite();
        sprite.setTextureRect(info.textureRect);

        visualObjectComponent.visualObjectPtr = visualObject;

        Core::Application::getInstance().getRenderVisualObjects()->addVisualObject(visualObjectComponent.visualObjectPtr, info.layerId);

        return entity;
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
