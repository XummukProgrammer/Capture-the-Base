#include "UpdateVisualObjectsSystem.hpp"

#include <core/Application.hpp>
#include <core/Assets.hpp>

#include <ecs/components/TransformComponent.hpp>
#include <ecs/components/VisualObjectComponent.hpp>
#include <ecs/components/TextureComponent.hpp>

namespace ECS
{
    void UpdateVisualObjectsSystem::onUpdate(float deltaTime, entt::registry& registry)
    {
        auto view = registry.view<UpdateVisualObjectComponent, VisualObjectComponent, TextureComponent, TransformComponent>();

        view.each([&registry](entt::entity entity, const UpdateVisualObjectComponent&, 
            VisualObjectComponent& visualObjectComponent, const TextureComponent& textureComponent, const TransformComponent& transformComponent) {
            sf::Sprite& sprite = visualObjectComponent.visualObjectPtr->getSprite();

            sprite.setPosition(transformComponent.position);
            sprite.setScale(transformComponent.scale);
            sprite.setRotation(transformComponent.rotation);

            if (auto asset = Core::Application::getInstance().getAssets()->getAsset<Core::AssetTexture>(textureComponent.assetId)) {
                sprite.setTexture(*asset);
            }
            sprite.setTextureRect(textureComponent.rectangle);

            registry.remove<UpdateVisualObjectComponent>(entity);
        });
    }
}
