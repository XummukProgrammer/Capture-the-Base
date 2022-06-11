#include "CellsECSUtils.hpp"

#include <core/Application.hpp>

#include <ecs/ECSWorld.hpp>
#include <ecs/utils/RenderVisualObjectsECSUtils.hpp>

namespace ECS
{
    entt::entity CellsECSUtils::createCell(const sf::Vector2f& startPosition, CellComponent::Type type, const sf::Vector2i& indexes,
        const TexturesPair& texturesPair, const sf::Vector2i& size)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        // Cell entity
        RenderVisualObjectsECSUtils::VisualObjectCreateInfo visualObjectCreateInfo;
        visualObjectCreateInfo.assetId = texturesPair.first;
        visualObjectCreateInfo.textureRect = { 0, 0, size.x, size.y };
        visualObjectCreateInfo.position = { startPosition.x + indexes.x * size.x, startPosition.y + indexes.y * size.y };
        auto cellEntity = RenderVisualObjectsECSUtils::createVisualObject(visualObjectCreateInfo);

        auto& cellComponent = registry.emplace<CellComponent>(cellEntity);
        cellComponent.type = type;
        cellComponent.indexes = indexes;

        // Outline entity
        visualObjectCreateInfo.assetId = texturesPair.second;
        cellComponent.outlineEntity = RenderVisualObjectsECSUtils::createVisualObject(visualObjectCreateInfo);

        return cellEntity;
    }

    void CellsECSUtils::createCellsBlock(const sf::Vector2f& startPosition,
        CellComponent::Type startType, const sf::Vector2i& indexes, TexturesMap& textures,
        const sf::Vector2i& size)
    {
        const auto secondType = startType == CellComponent::Type::White ? CellComponent::Type::Black : CellComponent::Type::White;

        auto createCellFn = [startPosition, startType, indexes, &textures, size](const sf::Vector2i& indexesOffset, CellComponent::Type cellType) {
            createCell(startPosition, startType, indexes + indexesOffset, textures[cellType], size);
        };

        createCellFn({ 0, 0 }, startType);
        createCellFn({ 1, 0 }, secondType);
    }

    void CellsECSUtils::createCells(const sf::Vector2f& startPosition, const sf::Vector2i& blocks,
        const std::string& whiteCellTextureAssetId, const std::string& whiteOutlineTextureAssetId,
        const std::string& blackCellTextureAssetId, const std::string& blackOutlineTextureAssetId,
        const sf::Vector2i& size)
    {
        sf::Vector2i indexes = { 0, 0 };
        std::map<CellComponent::Type, std::pair<std::string, std::string>> textures =
        {
            { CellComponent::Type::White, { whiteCellTextureAssetId, whiteOutlineTextureAssetId } },
            { CellComponent::Type::Black, { blackCellTextureAssetId, blackOutlineTextureAssetId } }
        };

        for (int y = 0; y < blocks.y; ++y) {
            const CellComponent::Type startType = y % 2 ? CellComponent::Type::Black : CellComponent::Type::White;

            for (int x = 0; x < blocks.x; ++x) {
                indexes = { x * 2, y };
                createCellsBlock(startPosition, startType, indexes, textures, size);
            }
        }
    }
}
