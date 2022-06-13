#include "GameApplicationDelegate.hpp"

#include <core/States.hpp>

#include <game/GameState.hpp>

#include <ecs/ECSWorld.hpp>
#include <ecs/utils/CellsUtils.hpp>
#include <ecs/utils/ChipsUtils.hpp>
#include <ecs/utils/TeamsUtils.hpp>
#include <ecs/utils/TextsUtils.hpp>
#include <ecs/systems/UpdateVisualObjectsSystem.hpp>
#include <ecs/systems/UpdateTextsSystem.hpp>
#include <ecs/systems/InputSystem.hpp>

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
        worldPtr->addSystem<ECS::InputSystem>();
        worldPtr->addSystem<ECS::UpdateVisualObjectsSystem>();
        worldPtr->addSystem<ECS::UpdateTextsSystem>();

        ECS::CellsUtils::CellsTextures cellsTextures;
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

        ECS::CellsUtils::CellFonts cellFonts;
        cellFonts.topFontAssetId = "DefaultFont";
        cellFonts.downFontAssetId = "DefaultFont";
        cellFonts.leftFontAssetId = "DefaultFont";
        cellFonts.rightFontAssetId = "DefaultFont";

        ECS::CellsUtils::createCells({ 50.f, 50.f }, { 4, 8 }, cellsTextures, { 64, 64 }, cellFonts);

        ECS::TeamsUtils::createTeam(ECS::ChipComponent::Type::Black, "Chip_Black", { 64, 64 }, { 0, 0 }, { 3, 3 });
        ECS::TeamsUtils::createTeam(ECS::ChipComponent::Type::White, "Chip_White", { 64, 64 }, { 5, 5 }, { 3, 3 });
    }
}
