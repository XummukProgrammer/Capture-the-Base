#include "UpdateTextsSystem.hpp"

#include <core/Application.hpp>
#include <core/Assets.hpp>

#include <ecs/components/TextComponent.hpp>
#include <ecs/components/TransformComponent.hpp>

namespace ECS
{
    void UpdateTextsSystem::onUpdate(float deltaTime, entt::registry& registry)
    {
        auto view = registry.view<UpdateTextComponent, TextComponent, TransformComponent>();
        view.each([&registry](entt::entity entity, const UpdateTextComponent&, TextComponent& textComponent, const TransformComponent& transformComponent) {
            auto& object = textComponent.object;
            if (auto asset = Core::Application::getInstance().getAssets()->getAsset<Core::AssetFont>(textComponent.fontAssetId)) {
                object.setFont(*asset);
            }
            object.setCharacterSize(textComponent.size);
            object.setString(textComponent.text);
            object.setFillColor(textComponent.color);
            object.setStyle(textComponent.style);
            object.setPosition(transformComponent.position);
            object.setScale(transformComponent.scale);
            object.setRotation(transformComponent.rotation);

            registry.remove<UpdateTextComponent>(entity);
        });
    }

    void UpdateTextsSystem::onDraw(entt::registry& registry, sf::RenderWindow* wndPtr)
    {
        auto view = registry.view<TextComponent>();
        view.each([wndPtr](entt::entity entity, TextComponent& textComponent) {
            wndPtr->draw(textComponent.object);
        });
    }
}
