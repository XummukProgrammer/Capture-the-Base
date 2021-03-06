#include "CellsUtils.hpp"

#include <core/Application.hpp>

#include <ecs/ECSWorld.hpp>
#include <ecs/utils/VisualObjectsUtils.hpp>
#include <ecs/utils/TextsUtils.hpp>
#include <ecs/utils/ChipsUtils.hpp>

#include <fmt/format.h>

namespace ECS
{
    entt::entity CellsUtils::createCell(const sf::Vector2f& startPosition, CellComponent::Type type, const sf::Vector2i& indexes,
        const CellTextures& textures, const sf::Vector2i& size, const CellFonts& cellFonts, const sf::Vector2i& maxIndexes)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        // Cell entity
        VisualObjectsUtils::VisualObjectCreateInfo visualObjectCreateInfo;
        visualObjectCreateInfo.layerName = "Cell";
        visualObjectCreateInfo.position = { startPosition.x + indexes.x * size.x, startPosition.y + indexes.y * size.y };
        VisualObjectsUtils::VisualObjectTextureInfo visualObjectTextureInfo;
        visualObjectTextureInfo.assetId = textures.baseAssetId;
        visualObjectTextureInfo.rectangle = { 0, 0, size.x, size.y };
        auto cellEntity = VisualObjectsUtils::create(visualObjectCreateInfo, visualObjectTextureInfo);

        auto& cellComponent = registry.emplace<CellComponent>(cellEntity);
        cellComponent.type = type;
        cellComponent.indexes = indexes;

        ECS::TextsUtils::TextCreateInfo textCreateInfo;

        if (indexes.x == 0) {
            // Outline left entity
            visualObjectTextureInfo.assetId = textures.outlineLeftAssetId;
            visualObjectCreateInfo.layerName = "CellOutline";
            cellComponent.outlineLeftEntity = VisualObjectsUtils::create(visualObjectCreateInfo, visualObjectTextureInfo);

            // Left text
            textCreateInfo.fontAssetId = cellFonts.leftFontAssetId;
            textCreateInfo.position = visualObjectCreateInfo.position - sf::Vector2f(25.f, -25.f);
            textCreateInfo.text = getCellTextIndex(maxIndexes.y, indexes.y);
            cellComponent.textLeftEntity = ECS::TextsUtils::createText(textCreateInfo);
        }

        if (indexes.y == 0) {
            // Outline top entity
            visualObjectTextureInfo.assetId = textures.outlineTopAssetId;
            visualObjectCreateInfo.layerName = "CellOutline";
            cellComponent.outlineTopEntity = VisualObjectsUtils::create(visualObjectCreateInfo, visualObjectTextureInfo);

            // Top text
            textCreateInfo.fontAssetId = cellFonts.topFontAssetId;
            textCreateInfo.text = getCellSymbol(cellComponent.indexes.x);
            textCreateInfo.position = visualObjectCreateInfo.position - sf::Vector2f(-25.f, 25.f);
            cellComponent.textTopEntity = ECS::TextsUtils::createText(textCreateInfo);
        }

        if (indexes.x == maxIndexes.x) {
            // Outline right entity
            visualObjectTextureInfo.assetId = textures.outlineRightAssetId;
            visualObjectCreateInfo.layerName = "CellOutline";
            cellComponent.outlineRightEntity = VisualObjectsUtils::create(visualObjectCreateInfo, visualObjectTextureInfo);

            // Right text
            textCreateInfo.fontAssetId = cellFonts.rightFontAssetId;
            textCreateInfo.position = visualObjectCreateInfo.position + sf::Vector2f(75.f, 25.f);
            textCreateInfo.text = getCellTextIndex(maxIndexes.y, indexes.y);
            cellComponent.textRightEntity = ECS::TextsUtils::createText(textCreateInfo);
        }

        if (indexes.y == maxIndexes.y) {
            // Outline down entity
            visualObjectTextureInfo.assetId = textures.outlineDownAssetId;
            visualObjectCreateInfo.layerName = "CellOutline";
            cellComponent.outlineDownEntity = VisualObjectsUtils::create(visualObjectCreateInfo, visualObjectTextureInfo);

            // Down text
            textCreateInfo.fontAssetId = cellFonts.downFontAssetId;
            textCreateInfo.position = visualObjectCreateInfo.position + sf::Vector2f(25.f, 60.f);
            textCreateInfo.text = getCellSymbol(cellComponent.indexes.x);
            cellComponent.textDownEntity = ECS::TextsUtils::createText(textCreateInfo);
        }

        visualObjectCreateInfo.isVisible = false;

        // Moveable
        visualObjectTextureInfo.assetId = textures.moveableAssetId;
        visualObjectCreateInfo.layerName = "CellMoveable";
        cellComponent.moveableEntity = VisualObjectsUtils::create(visualObjectCreateInfo, visualObjectTextureInfo);

        // Selected
        visualObjectTextureInfo.assetId = textures.selectedAssetId;
        visualObjectCreateInfo.layerName = "CellSelected";
        cellComponent.selectedEntity = VisualObjectsUtils::create(visualObjectCreateInfo, visualObjectTextureInfo);

        return cellEntity;
    }

    void CellsUtils::createCellsBlock(const sf::Vector2f& startPosition,
        CellComponent::Type startType, const sf::Vector2i& indexes, const CellsTextures& cellsTextures,
        const sf::Vector2i& size, const CellFonts& cellFonts, const sf::Vector2i& maxIndexes)
    {
        const auto secondType = startType == CellComponent::Type::White ? CellComponent::Type::Black : CellComponent::Type::White;

        auto createCellFn = [startPosition, indexes, cellsTextures, size, cellFonts, maxIndexes](const sf::Vector2i& indexesOffset, CellComponent::Type cellType) {
            auto& textures = cellType == CellComponent::Type::White ? cellsTextures.whiteCellTextures : cellsTextures.blackCellTextures;
            createCell(startPosition, cellType, indexes + indexesOffset, textures, size, cellFonts, maxIndexes);
        };

        createCellFn({ 0, 0 }, startType);
        createCellFn({ 1, 0 }, secondType);
    }

    void CellsUtils::createCells(const sf::Vector2f& startPosition, const sf::Vector2i& blocks,
        const CellsTextures& cellsTextures,
        const sf::Vector2i& size, const CellFonts& cellFonts)
    {
        // Create cells
        sf::Vector2i maxIndexes = { blocks.x * 2 - 1, blocks.y - 1 };
        sf::Vector2i indexes = { 0, 0 };
        for (int y = 0; y < blocks.y; ++y) {
            const CellComponent::Type startType = y % 2 ? CellComponent::Type::Black : CellComponent::Type::White;

            for (int x = 0; x < blocks.x; ++x) {
                indexes = { x * 2, y };
                createCellsBlock(startPosition, startType, indexes, cellsTextures, size, cellFonts, maxIndexes);
            }
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

    std::vector<entt::entity> CellsUtils::getAvailableCellsFromIndexes(const sf::Vector2i& indexes)
    {
        const std::vector<sf::Vector2i> availableIndexes = {
            { indexes.x, indexes.y - 1 },
            { indexes.x, indexes.y + 1 },
            { indexes.x - 1, indexes.y },
            { indexes.x + 1, indexes.y }
        };
        std::vector<entt::entity> entities;
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();
        auto view = registry.view<CellComponent>();

        view.each([availableIndexes, &entities](entt::entity entity, const CellComponent& cellComponent) {
            for (const auto& indexes : availableIndexes) {
                if (indexes == cellComponent.indexes) {
                    entities.push_back(entity);
                }
            }
        });

        return entities;
    }

    std::vector<entt::entity> CellsUtils::getMoveableCellsFromIndexes(const sf::Vector2i& indexes)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        auto&& availableCells = getAvailableCellsFromIndexes(indexes);
        std::vector<entt::entity> moveableCells;

        for (const auto availableCell : availableCells) {
            auto& cellComponent = registry.get<CellComponent>(availableCell);
            auto availableChip = ChipsUtils::getChipFromIndexes(cellComponent.indexes);
            if (!registry.valid(availableChip)) {
                moveableCells.push_back(availableCell);
            }
        }

        return moveableCells;
    }

    void CellsUtils::setMoveableCell(entt::entity entity)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        if (auto cellComponent = registry.try_get<CellComponent>(entity)) {
            VisualObjectsUtils::show(cellComponent->moveableEntity);
        }

        registry.emplace_or_replace<CellMoveableComponent>(entity);
    }

    void CellsUtils::unsetMoveableCell(entt::entity entity)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        if (auto cellComponent = registry.try_get<CellComponent>(entity)) {
            VisualObjectsUtils::hide(cellComponent->moveableEntity);
        }

        registry.remove<CellMoveableComponent>(entity);
    }

    void CellsUtils::unsetMoveableCells()
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();
        auto view = registry.view<CellMoveableComponent>();

        view.each([](entt::entity entity, const CellMoveableComponent&) {
            unsetMoveableCell(entity);
        });
    }

    std::string CellsUtils::getCellTextIndex(int maxY, int cellY)
    {
        return std::to_string(maxY - cellY + 1);
    }

    std::string CellsUtils::getCellSymbol(int cellX)
    {
        static char symbols[] = "abcdefgh";
        return fmt::format("{}", symbols[cellX]);
    }
}
