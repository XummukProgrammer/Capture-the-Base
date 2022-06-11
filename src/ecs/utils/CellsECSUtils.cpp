#include "CellsECSUtils.hpp"

#include <core/Application.hpp>

#include <ecs/ECSWorld.hpp>
#include <ecs/utils/RenderVisualObjectsECSUtils.hpp>

namespace ECS
{
    entt::entity CellsECSUtils::createCell(const sf::Vector2f& startPosition, CellComponent::Type type, const sf::Vector2i& indexes,
        const CellTextures& textures, const sf::Vector2i& size)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        // Cell entity
        RenderVisualObjectsECSUtils::VisualObjectCreateInfo visualObjectCreateInfo;
        visualObjectCreateInfo.assetId = textures.baseAssetId;
        visualObjectCreateInfo.layerName = "Cell";
        visualObjectCreateInfo.textureRect = { 0, 0, size.x, size.y };
        visualObjectCreateInfo.position = { startPosition.x + indexes.x * size.x, startPosition.y + indexes.y * size.y };
        auto cellEntity = RenderVisualObjectsECSUtils::createVisualObject(visualObjectCreateInfo);

        auto& cellComponent = registry.emplace<CellComponent>(cellEntity);
        cellComponent.type = type;
        cellComponent.indexes = indexes;

        visualObjectCreateInfo.isVisible = false;

        // Outline top entity
        visualObjectCreateInfo.assetId = textures.outlineTopAssetId;
        visualObjectCreateInfo.layerName = "CellOutline";
        cellComponent.outlineTopEntity = RenderVisualObjectsECSUtils::createVisualObject(visualObjectCreateInfo);

        // Outline down entity
        visualObjectCreateInfo.assetId = textures.outlineDownAssetId;
        visualObjectCreateInfo.layerName = "CellOutline";
        cellComponent.outlineDownEntity = RenderVisualObjectsECSUtils::createVisualObject(visualObjectCreateInfo);

        // Outline left entity
        visualObjectCreateInfo.assetId = textures.outlineLeftAssetId;
        visualObjectCreateInfo.layerName = "CellOutline";
        cellComponent.outlineLeftEntity = RenderVisualObjectsECSUtils::createVisualObject(visualObjectCreateInfo);

        // Outline right entity
        visualObjectCreateInfo.assetId = textures.outlineRightAssetId;
        visualObjectCreateInfo.layerName = "CellOutline";
        cellComponent.outlineRightEntity = RenderVisualObjectsECSUtils::createVisualObject(visualObjectCreateInfo);

        // Moveable
        visualObjectCreateInfo.assetId = textures.moveableAssetId;
        visualObjectCreateInfo.layerName = "CellMoveable";
        cellComponent.moveableEntity = RenderVisualObjectsECSUtils::createVisualObject(visualObjectCreateInfo);

        // Selected
        visualObjectCreateInfo.assetId = textures.selectedAssetId;
        visualObjectCreateInfo.layerName = "CellSelected";
        cellComponent.selectedEntity = RenderVisualObjectsECSUtils::createVisualObject(visualObjectCreateInfo);

        return cellEntity;
    }

    void CellsECSUtils::createCellsBlock(const sf::Vector2f& startPosition,
        CellComponent::Type startType, const sf::Vector2i& indexes, const CellsTextures& cellsTextures,
        const sf::Vector2i& size)
    {
        const auto secondType = startType == CellComponent::Type::White ? CellComponent::Type::Black : CellComponent::Type::White;

        auto createCellFn = [startPosition, indexes, &cellsTextures, size](const sf::Vector2i& indexesOffset, CellComponent::Type cellType) {
            auto& textures = cellType == CellComponent::Type::White ? cellsTextures.whiteCellTextures : cellsTextures.blackCellTextures;
            createCell(startPosition, cellType, indexes + indexesOffset, textures, size);
        };

        createCellFn({ 0, 0 }, startType);
        createCellFn({ 1, 0 }, secondType);
    }

    void CellsECSUtils::createCells(const sf::Vector2f& startPosition, const sf::Vector2i& blocks,
        const CellsTextures& cellsTextures,
        const sf::Vector2i& size)
    {
        sf::Vector2i indexes = { 0, 0 };

        for (int y = 0; y < blocks.y; ++y) {
            const CellComponent::Type startType = y % 2 ? CellComponent::Type::Black : CellComponent::Type::White;

            for (int x = 0; x < blocks.x; ++x) {
                indexes = { x * 2, y };
                createCellsBlock(startPosition, startType, indexes, cellsTextures, size);
            }
        }
    }

    entt::entity CellsECSUtils::getCellFromIndexes(const sf::Vector2i& indexes)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();
        auto view = registry.view<CellComponent>();

        for (auto entity : view) {
            auto& cellComponent = registry.get<CellComponent>(entity);
            if (cellComponent.indexes == indexes) {
                return entity;
            }
        }

        return entt::null;
    }
}
