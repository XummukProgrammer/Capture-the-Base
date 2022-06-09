#include "GameApplicationDelegate.hpp"

#include <core/States.hpp>
#include <core/RenderVisualObjects.hpp>

#include <game/GameState.hpp>

namespace Game
{
    void GameApplicationDelegate::onInitStates(Core::States* statesPtr)
    {
        auto gameState = std::make_unique<GameState>();
        statesPtr->addState("GameState", std::move(gameState));

        statesPtr->setCurrentState("GameState");
    }

    void GameApplicationDelegate::onInitRenderVisualObjects(Core::RenderVisualObjects* renderVisualObjectsPtr)
    {
        auto visualObject = std::make_shared<Core::VisualObject>();
        visualObject->loadFromAsset("test");
        renderVisualObjectsPtr->addVisualObject(visualObject);
    }
}
