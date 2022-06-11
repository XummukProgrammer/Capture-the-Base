#include "CellsECSUtils.hpp"

#include <core/Application.hpp>

#include <ecs/ECSWorld.hpp>
#include <ecs/utils/RenderVisualObjectsECSUtils.hpp>

namespace ECS
{
    entt::entity CellsECSUtils::createCell(const sf::Vector2f& startPosition, CellComponent::Type type, const sf::Vector2i& indexes,
        const std::string& cellTextureAssetId, const std::string& outlineTextureAssetId, const sf::Vector2i& size)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        RenderVisualObjectsECSUtils::VisualObjectCreateInfo visualObjectCreateInfo;
        visualObjectCreateInfo.assetId = cellTextureAssetId;
        visualObjectCreateInfo.textureRect = { 0, 0, size.x, size.y };
        visualObjectCreateInfo.position = { startPosition.x + indexes.x * size.x, startPosition.y + indexes.y * size.y };
        auto cellEntity = RenderVisualObjectsECSUtils::createVisualObject(visualObjectCreateInfo);

        auto& cellComponent = registry.emplace<CellComponent>(cellEntity);
        cellComponent.type = type;
        cellComponent.indexes = indexes;

        // TODO: Create outline entity

        return cellEntity;
    }

    std::tuple<entt::entity, entt::entity> CellsECSUtils::createCellsBlock(const sf::Vector2f& startPosition,
        CellComponent::Type startType, const sf::Vector2i& indexes,
        const std::string& whiteCellTextureAssetId, const std::string& whiteOutlineTextureAssetId,
        const std::string& blackCellTextureAssetId, const std::string& blackOutlineTextureAssetId,
        const sf::Vector2i& size)
    {
        CellComponent::Type secondType = startType == CellComponent::Type::White ? CellComponent::Type::Black : CellComponent::Type::White;
        std::map<CellComponent::Type, std::pair<std::string, std::string>> textures =
        {
            { CellComponent::Type::White, { whiteCellTextureAssetId, whiteOutlineTextureAssetId } },
            { CellComponent::Type::Black, { blackCellTextureAssetId, blackOutlineTextureAssetId } }
        };

        return { 
            createCell(startPosition, startType, indexes, textures[startType].first, textures[startType].second, size),
            createCell(startPosition, secondType, { indexes.x + 1, indexes.y },
                textures[secondType].first, textures[secondType].second, size)
        };
    }

    void CellsECSUtils::createCells(const sf::Vector2f& startPosition, const sf::Vector2i& blocks,
        const std::string& whiteCellTextureAssetId, const std::string& whiteOutlineTextureAssetId,
        const std::string& blackCellTextureAssetId, const std::string& blackOutlineTextureAssetId,
        const sf::Vector2i& size)
    {
        sf::Vector2i indexes = { 0, 0 };

        for (int y = 0; y < blocks.y; ++y) {
            const CellComponent::Type startType = y % 2 ? CellComponent::Type::Black : CellComponent::Type::White;

            for (int x = 0; x < blocks.x; ++x) {
                indexes = { x * 2, y };
                createCellsBlock(startPosition, startType, indexes, whiteCellTextureAssetId, whiteOutlineTextureAssetId,
                    blackCellTextureAssetId, blackOutlineTextureAssetId,
                    size);
            }
        }
    }
}
