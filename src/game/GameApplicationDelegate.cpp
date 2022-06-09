#include "GameApplicationDelegate.hpp"

#include <core/States.hpp>
#include <core/RenderVisualObjects.hpp>

#include <game/GameState.hpp>

#include <ecs/utils/RenderVisualObjectsECSUtils.hpp>

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
        entt::entity test1 = ECS::RenderVisualObjectsECSUtils::createVisualObject("test");

        entt::entity test2 = ECS::RenderVisualObjectsECSUtils::createVisualObject("test2");
        ECS::RenderVisualObjectsECSUtils::removeVisualObject(test2);
    }
}
