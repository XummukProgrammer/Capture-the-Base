#include "RenderVisualObjectsECSUtils.hpp"

#include <core/Application.hpp>
#include <core/VisualObjects.hpp>

#include <ecs/ECSWorld.hpp>
#include <ecs/components/TransformComponent.hpp>
#include <ecs/components/VisualObjectComponent.hpp>
#include <ecs/components/TextureComponent.hpp>

namespace ECS
{
    entt::entity RenderVisualObjectsECSUtils::create(const VisualObjectCreateInfo& info)
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
        
        if (info.isVisible) {
            visualObject->show();
        } else {
            visualObject->hide();
        }

        visualObjectComponent.visualObjectPtr = visualObject;

        Core::Application::getInstance().getVisualObjects()->add(visualObjectComponent.visualObjectPtr, info.layerName);

        return entity;
    }

    void RenderVisualObjectsECSUtils::move(entt::entity entity, int newLayerId)
    {
        entt::registry& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        if (auto visualObjectComponent = registry.try_get<ECS::VisualObjectComponent>(entity)) {
            Core::Application::getInstance().getVisualObjects()->move(visualObjectComponent->visualObjectPtr, newLayerId);
        }
    }

    void RenderVisualObjectsECSUtils::moveUp(entt::entity entity)
    {
        entt::registry& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        if (auto visualObjectComponent = registry.try_get<ECS::VisualObjectComponent>(entity)) {
            Core::Application::getInstance().getVisualObjects()->moveUp(visualObjectComponent->visualObjectPtr);
        }
    }

    void RenderVisualObjectsECSUtils::moveDown(entt::entity entity)
    {
        entt::registry& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        if (auto visualObjectComponent = registry.try_get<ECS::VisualObjectComponent>(entity)) {
            Core::Application::getInstance().getVisualObjects()->moveDown(visualObjectComponent->visualObjectPtr);
        }
    }

    void RenderVisualObjectsECSUtils::remove(entt::entity entity)
    {
        entt::registry& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        if (auto visualObjectComponent = registry.try_get<ECS::VisualObjectComponent>(entity)) {
            Core::Application::getInstance().getVisualObjects()->remove(visualObjectComponent->visualObjectPtr);
            visualObjectComponent->visualObjectPtr.reset();
        }

        registry.destroy(entity);
    }

    void RenderVisualObjectsECSUtils::show(entt::entity entity)
    {
        entt::registry& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        if (auto visualObjectComponent = registry.try_get<ECS::VisualObjectComponent>(entity)) {
            visualObjectComponent->visualObjectPtr->show();
        }
    }

    void RenderVisualObjectsECSUtils::hide(entt::entity entity)
    {
        entt::registry& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        if (auto visualObjectComponent = registry.try_get<ECS::VisualObjectComponent>(entity)) {
            visualObjectComponent->visualObjectPtr->hide();
        }
    }

    void RenderVisualObjectsECSUtils::setTexture(entt::entity entity, const VisualObjectTextureInfo& info)
    {
        entt::registry& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        auto& textureComponent = registry.get_or_emplace<TextureComponent>(entity);
        if (info.assetId) {
            textureComponent.assetId = info.assetId.value();
        }
        if (info.rectangle) {
            textureComponent.rectangle = info.rectangle.value();
        }

        if (auto visualObjectComponent = registry.try_get<ECS::VisualObjectComponent>(entity)) {
            visualObjectComponent->visualObjectPtr->loadFromAsset(textureComponent.assetId);
            visualObjectComponent->visualObjectPtr->getSprite().setTextureRect(textureComponent.rectangle);
        }
    }
}
