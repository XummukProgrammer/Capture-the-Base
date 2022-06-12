#include "ChipsUtils.hpp"

#include "CellsUtils.hpp"
#include <ecs/utils/VisualObjectsUtils.hpp>

#include <core/Application.hpp>

#include <ecs/ECSWorld.hpp>
#include <ecs/components/TransformComponent.hpp>
#include <ecs/components/ChipComponent.hpp>

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
        auto entity = VisualObjectsUtils::create(visualObjectCreateInfo);
        VisualObjectsUtils::setTexture(entity, visualObjectTextureInfo);

        auto& chipComponent = registry.emplace<ChipComponent>(entity);
        chipComponent.type = type;
        chipComponent.indexes = indexes;

        return entity;
    }
}
