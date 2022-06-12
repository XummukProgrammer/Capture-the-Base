#include "CellsUtils.hpp"

#include <core/Application.hpp>

#include <ecs/ECSWorld.hpp>
#include <ecs/utils/VisualObjectsUtils.hpp>

namespace ECS
{
    entt::entity CellsUtils::createCell(const sf::Vector2f& startPosition, CellComponent::Type type, const sf::Vector2i& indexes,
        const CellTextures& textures, const sf::Vector2i& size)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        // Cell entity
        VisualObjectsUtils::VisualObjectCreateInfo visualObjectCreateInfo;
        visualObjectCreateInfo.layerName = "Cell";
        visualObjectCreateInfo.position = { startPosition.x + indexes.x * size.x, startPosition.y + indexes.y * size.y };
        VisualObjectsUtils::VisualObjectTextureInfo visualObjectTextureInfo;
        visualObjectTextureInfo.assetId = textures.baseAssetId;
        visualObjectTextureInfo.rectangle = { 0, 0, size.x, size.y };
        auto cellEntity = VisualObjectsUtils::create(visualObjectCreateInfo);
        VisualObjectsUtils::setTexture(cellEntity, visualObjectTextureInfo);

        auto& cellComponent = registry.emplace<CellComponent>(cellEntity);
        cellComponent.type = type;
        cellComponent.indexes = indexes;

        visualObjectCreateInfo.isVisible = false;

        // Outline top entity
        visualObjectTextureInfo.assetId = textures.outlineTopAssetId;
        visualObjectCreateInfo.layerName = "CellOutline";
        cellComponent.outlineTopEntity = VisualObjectsUtils::create(visualObjectCreateInfo);
        VisualObjectsUtils::setTexture(cellComponent.outlineTopEntity, visualObjectTextureInfo);

        // Outline down entity
        visualObjectTextureInfo.assetId = textures.outlineDownAssetId;
        visualObjectCreateInfo.layerName = "CellOutline";
        cellComponent.outlineDownEntity = VisualObjectsUtils::create(visualObjectCreateInfo);
        VisualObjectsUtils::setTexture(cellComponent.outlineDownEntity, visualObjectTextureInfo);

        // Outline left entity
        visualObjectTextureInfo.assetId = textures.outlineLeftAssetId;
        visualObjectCreateInfo.layerName = "CellOutline";
        cellComponent.outlineLeftEntity = VisualObjectsUtils::create(visualObjectCreateInfo);
        VisualObjectsUtils::setTexture(cellComponent.outlineLeftEntity, visualObjectTextureInfo);

        // Outline right entity
        visualObjectTextureInfo.assetId = textures.outlineRightAssetId;
        visualObjectCreateInfo.layerName = "CellOutline";
        cellComponent.outlineRightEntity = VisualObjectsUtils::create(visualObjectCreateInfo);
        VisualObjectsUtils::setTexture(cellComponent.outlineRightEntity, visualObjectTextureInfo);

        // Moveable
        visualObjectTextureInfo.assetId = textures.moveableAssetId;
        visualObjectCreateInfo.layerName = "CellMoveable";
        cellComponent.moveableEntity = VisualObjectsUtils::create(visualObjectCreateInfo);
        VisualObjectsUtils::setTexture(cellComponent.moveableEntity, visualObjectTextureInfo);

        // Selected
        visualObjectTextureInfo.assetId = textures.selectedAssetId;
        visualObjectCreateInfo.layerName = "CellSelected";
        cellComponent.selectedEntity = VisualObjectsUtils::create(visualObjectCreateInfo);
        VisualObjectsUtils::setTexture(cellComponent.selectedEntity, visualObjectTextureInfo);

        return cellEntity;
    }

    void CellsUtils::createCellsBlock(const sf::Vector2f& startPosition,
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

    void CellsUtils::createCells(const sf::Vector2f& startPosition, const sf::Vector2i& blocks,
        const CellsTextures& cellsTextures,
        const sf::Vector2i& size)
    {
        // Create cells
        sf::Vector2i indexes = { 0, 0 };
        for (int y = 0; y < blocks.y; ++y) {
            const CellComponent::Type startType = y % 2 ? CellComponent::Type::Black : CellComponent::Type::White;

            for (int x = 0; x < blocks.x; ++x) {
                indexes = { x * 2, y };
                createCellsBlock(startPosition, startType, indexes, cellsTextures, size);
            }
        }

        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        // Init frame
        ++indexes.x;

        {
            auto view = registry.view<CellComponent>();
            view.each([&indexes](CellComponent& cellComponent) {
                if (cellComponent.indexes.x == 0) {
                    VisualObjectsUtils::show(cellComponent.outlineLeftEntity);
                }

                if (cellComponent.indexes.y == 0) {
                    VisualObjectsUtils::show(cellComponent.outlineTopEntity);
                }

                if (cellComponent.indexes.x == indexes.x) {
                    VisualObjectsUtils::show(cellComponent.outlineRightEntity);
                }

                if (cellComponent.indexes.y == indexes.y) {
                    VisualObjectsUtils::show(cellComponent.outlineDownEntity);
                }
            });
        }
    }

    entt::entity CellsUtils::getCellFromIndexes(const sf::Vector2i& indexes)
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
