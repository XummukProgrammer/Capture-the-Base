#include "GameApplicationDelegate.hpp"

#include <core/States.hpp>
#include <core/RenderVisualObjects.hpp>

#include <game/GameState.hpp>

#include <ecs/ECSWorld.hpp>
#include <ecs/utils/CellsECSUtils.hpp>
#include <ecs/utils/ChipsECSUtils.hpp>
#include <ecs/systems/UpdateVisualObjectsSystem.hpp>

namespace Game
{
    void GameApplicationDelegate::onInitStates(Core::States* statesPtr)
    {
        auto gameState = std::make_unique<GameState>();
        statesPtr->addState("GameState", std::move(gameState));

        statesPtr->setCurrentState("GameState");
    }

    void GameApplicationDelegate::onInitECSWorld(ECS::World* worldPtr)
    {
        worldPtr->addSystem<ECS::UpdateVisualObjectsSystem>();

        ECS::CellsECSUtils::CellsTextures cellsTextures;
        cellsTextures.whiteCellTextures.baseAssetId = "Cell_White";
        cellsTextures.whiteCellTextures.outlineTopAssetId = "Cell_Outline_Top";
        cellsTextures.whiteCellTextures.outlineDownAssetId = "Cell_Outline_Down";
        cellsTextures.whiteCellTextures.outlineLeftAssetId = "Cell_Outline_Left";
        cellsTextures.whiteCellTextures.outlineRightAssetId = "Cell_Outline_Right";
        cellsTextures.whiteCellTextures.moveableAssetId = "Cell_Moveable";
        cellsTextures.whiteCellTextures.selectedAssetId = "Cell_Selected";

        cellsTextures.blackCellTextures.baseAssetId = "Cell_Black";
        cellsTextures.blackCellTextures.outlineTopAssetId = "Cell_Outline_Top";
        cellsTextures.blackCellTextures.outlineDownAssetId = "Cell_Outline_Down";
        cellsTextures.blackCellTextures.outlineLeftAssetId = "Cell_Outline_Left";
        cellsTextures.blackCellTextures.outlineRightAssetId = "Cell_Outline_Right";
        cellsTextures.blackCellTextures.moveableAssetId = "Cell_Moveable";
        cellsTextures.blackCellTextures.selectedAssetId = "Cell_Selected";

        ECS::CellsECSUtils::createCells({ 50.f, 50.f }, { 4, 8 }, cellsTextures, { 64, 64 });

        ECS::ChipsECSUtils::createChip(ECS::ChipComponent::Type::White, { 1, 0 }, "Chip_White", { 64, 64 });
    }
}
