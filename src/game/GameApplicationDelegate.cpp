#include "GameApplicationDelegate.hpp"

#include <core/States.hpp>
#include <core/RenderVisualObjects.hpp>

#include <game/GameState.hpp>

#include <ecs/ECSWorld.hpp>
#include <ecs/utils/RenderVisualObjectsECSUtils.hpp>
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

        entt::entity test1 = ECS::RenderVisualObjectsECSUtils::createVisualObject("test", 0, { 50.f, 50.f }, { 0.5f, 0.5f }, 60.f);
    }
}
