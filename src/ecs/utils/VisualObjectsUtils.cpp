#include "VisualObjectsUtils.hpp"

#include <core/Application.hpp>
#include <core/VisualObjects.hpp>

#include <ecs/ECSWorld.hpp>
#include <ecs/components/TransformComponent.hpp>
#include <ecs/components/VisualObjectComponent.hpp>
#include <ecs/components/TextureComponent.hpp>

namespace ECS
{
    entt::entity VisualObjectsUtils::create(const VisualObjectCreateInfo& objectInfo, const VisualObjectTextureInfo& textureInfo)
    {
        entt::registry& registry = Core::Application::getInstance().getECSWorld()->getRegistry();
        entt::entity entity = registry.create();

        ECS::TransformComponent& transformComponent = registry.emplace<ECS::TransformComponent>(entity);
        transformComponent.position = objectInfo.position;
        transformComponent.scale = objectInfo.scale;
        transformComponent.rotation = objectInfo.rotation;

        // Load Visual Object
        ECS::VisualObjectComponent& visualObjectComponent = registry.emplace<ECS::VisualObjectComponent>(entity);
        
        auto visualObject = std::make_shared<Core::VisualObject>();
        
        if (objectInfo.isVisible) {
            visualObject->show();
        } else {
            visualObject->hide();
        }

        visualObjectComponent.visualObjectPtr = visualObject;

        updateTexture(entity, textureInfo);
        //registry.emplace<UpdateVisualObjectComponent>(entity);

        Core::Application::getInstance().getVisualObjects()->add(visualObjectComponent.visualObjectPtr, objectInfo.layerName);

        return entity;
    }

    void VisualObjectsUtils::move(entt::entity entity, int newLayerId)
    {
        entt::registry& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        if (auto visualObjectComponent = registry.try_get<ECS::VisualObjectComponent>(entity)) {
            Core::Application::getInstance().getVisualObjects()->move(visualObjectComponent->visualObjectPtr, newLayerId);
        }
    }

    void VisualObjectsUtils::remove(entt::entity entity)
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

    void VisualObjectsUtils::show(entt::entity entity)
    {
        entt::registry& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        if (auto visualObjectComponent = registry.try_get<ECS::VisualObjectComponent>(entity)) {
            visualObjectComponent->visualObjectPtr->show();
        }
    }

    void VisualObjectsUtils::hide(entt::entity entity)
    {
        entt::registry& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        if (auto visualObjectComponent = registry.try_get<ECS::VisualObjectComponent>(entity)) {
            visualObjectComponent->visualObjectPtr->hide();
        }
    }

    void VisualObjectsUtils::updateTexture(entt::entity entity, const VisualObjectTextureInfo& info)
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

        registry.emplace_or_replace<UpdateVisualObjectComponent>(entity);
    }
}
