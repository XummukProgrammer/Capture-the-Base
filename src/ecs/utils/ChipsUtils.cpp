#include "ChipsUtils.hpp"

#include "CellsUtils.hpp"
#include <ecs/utils/VisualObjectsUtils.hpp>

#include <core/Application.hpp>

#include <ecs/ECSWorld.hpp>
#include <ecs/components/TransformComponent.hpp>
#include <ecs/components/ChipComponent.hpp>
#include <ecs/components/VisualObjectComponent.hpp>

namespace ECS
{
    entt::entity ChipsUtils::createChip(ChipComponent::Type type, const sf::Vector2i& indexes,
        const std::string& textureAssetId, const sf::Vector2i& size)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        sf::Vector2f position;
        {
            auto cellEntity = CellsUtils::getCellFromIndexes(indexes);
            if (registry.valid(cellEntity)) {
                if (auto transformComponent = registry.try_get<TransformComponent>(cellEntity)) {
                    position = transformComponent->position;
                }
            }
        }

        VisualObjectsUtils::VisualObjectCreateInfo visualObjectCreateInfo;
        visualObjectCreateInfo.layerName = "Chip";
        visualObjectCreateInfo.position = position;
        VisualObjectsUtils::VisualObjectTextureInfo visualObjectTextureInfo;
        visualObjectTextureInfo.assetId = textureAssetId;
        visualObjectTextureInfo.rectangle = { 0, 0, size.x, size.y };
        auto entity = VisualObjectsUtils::create(visualObjectCreateInfo, visualObjectTextureInfo);

        auto& chipComponent = registry.emplace<ChipComponent>(entity);
        chipComponent.type = type;
        chipComponent.indexes = indexes;

        return entity;
    }

    entt::entity ChipsUtils::getChipFromIndexes(const sf::Vector2i& indexes)
    {
        entt::entity entity_ = entt::null;
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();
        auto view = registry.view<ChipComponent>();

        view.each([&entity_, indexes](entt::entity entity, const ChipComponent& chipComponent) {
            if (indexes == chipComponent.indexes) {
                entity_ = entity;
            }
        });

        return entity_;
    }

    void ChipsUtils::setTargetChip(entt::entity entity)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        registry.emplace_or_replace<ChipTargetComponent>(entity);
    }

    void ChipsUtils::unsetTargetChip(entt::entity entity)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        registry.remove<ChipTargetComponent>(entity);
    }

    void ChipsUtils::unsetTargetChip()
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();
        auto view = registry.view<ChipTargetComponent>();

        view.each([](entt::entity entity, const ChipTargetComponent&) {
            unsetTargetChip(entity);
        });
    }

    entt::entity ChipsUtils::getTargetChip()
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();
        auto view = registry.view<ChipTargetComponent>();
        for (auto entity : view) {
            return entity;
        }
        return entt::null;
    }

    void ChipsUtils::moveChip(entt::entity entity, const sf::Vector2i& newIndexes)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        sf::Vector2f newPosition;
        {
            auto cellEntity = CellsUtils::getCellFromIndexes(newIndexes);
            if (registry.valid(cellEntity)) {
                if (auto transformComponent = registry.try_get<TransformComponent>(cellEntity)) {
                    newPosition = transformComponent->position;
                }
            }
        }

        if (auto chipComponent = registry.try_get<ChipComponent>(entity)) {
            chipComponent->indexes = newIndexes;
        }

        if (auto transformComponent = registry.try_get<TransformComponent>(entity)) {
            transformComponent->position = newPosition;
        }

        registry.emplace_or_replace<UpdateVisualObjectComponent>(entity);
    }
}
