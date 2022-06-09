#include "UpdateVisualObjectsSystem.hpp"

#include <ecs/components/TransformComponent.hpp>
#include <ecs/Components/VisualObjectComponent.hpp>

namespace ECS
{
    void UpdateVisualObjectsSystem::onUpdate(float deltaTime, entt::registry& registry)
    {
        auto view = registry.view<TransformComponent, VisualObjectComponent>();

        view.each([](entt::entity entity, const TransformComponent& transformComponent, VisualObjectComponent& visualObjectComponent) {
            sf::Sprite& sprite = visualObjectComponent.visualObjectPtr->getSprite();

            sprite.setPosition(transformComponent.position);
            sprite.setScale(transformComponent.scale);
            sprite.setRotation(transformComponent.rotation);
        });
    }
}
