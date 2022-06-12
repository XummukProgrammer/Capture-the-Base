#include "TextsUtils.hpp"

#include <core/Application.hpp>

#include <ecs/ECSWorld.hpp>
#include <ecs/components/TextComponent.hpp>
#include <ecs/components/TransformComponent.hpp>

namespace ECS
{
    entt::entity TextsUtils::createText(const TextCreateInfo& info)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();
        auto entity = registry.create();
        updateText(entity, info);
        return entity;
    }

    void TextsUtils::updateText(entt::entity entity, const TextCreateInfo& info)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        auto& textComponent = registry.get_or_emplace<TextComponent>(entity);
        textComponent.fontAssetId = info.fontAssetId;
        textComponent.text = info.text;
        textComponent.size = info.size;
        textComponent.color = info.color;
        textComponent.style = info.style;

        auto& transformComponent = registry.get_or_emplace<TransformComponent>(entity);
        transformComponent.position = info.position;
        transformComponent.scale = info.scale;
        transformComponent.rotation = info.rotation;

        registry.emplace<UpdateTextComponent>(entity);
    }
}
