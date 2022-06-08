#include "GameApplicationDelegate.hpp"

#include <core/States.hpp>

#include <game/GameState.hpp>

namespace Game
{
    void GameApplicationDelegate::onInitStates(Core::States* statesPtr)
    {
        auto gameState = std::make_unique<GameState>();
        statesPtr->addState("GameState", std::move(gameState));

        statesPtr->setCurrentState("GameState");
    }
}
