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

        if (!registry.valid(entity)) {
            return;
        }

        auto& textComponent = registry.get_or_emplace<TextComponent>(entity);
        textComponent.fontAssetId = info.fontAssetId;
        textComponent.text = info.text;
        textComponent.size = info.size;
        textComponent.color = info.color;
        textComponent.style = info.style;
        textComponent.isVisible = info.isVisible;

        auto& transformComponent = registry.get_or_emplace<TransformComponent>(entity);
        transformComponent.position = info.position;
        transformComponent.scale = info.scale;
        transformComponent.rotation = info.rotation;

        registry.emplace<UpdateTextComponent>(entity);
    }

    void TextsUtils::showText(entt::entity entity, const std::string& text)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        if (auto textComponent = registry.try_get<TextComponent>(entity)) {
            textComponent->isVisible = true;
            textComponent->text = text;
        }

        registry.emplace_or_replace<UpdateTextComponent>(entity);
    }

    void TextsUtils::hideText(entt::entity entity)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        if (auto textComponent = registry.try_get<TextComponent>(entity)) {
            textComponent->isVisible = false;
        }

        registry.emplace_or_replace<UpdateTextComponent>(entity);
    }
}
