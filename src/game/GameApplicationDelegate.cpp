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

        ECS::CellsECSUtils::createCells({ 50.f, 50.f }, { 4, 8 }, 
            "Cell_White", "Cell_White_Outline",
            "Cell_Black", "Cell_Black_Outline",
            { 64, 64 });

        ECS::ChipsECSUtils::createChip(ECS::ChipComponent::Type::White, { 1, 0 }, "Chip_White", { 64, 64 });
    }
}
