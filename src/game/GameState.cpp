#include "GameState.hpp"

#include <core/Application.hpp>
#include <core/Store.hpp>

namespace Game
{
    void GameState::onEnter()
    {
        _gameDataStore = Core::Application::getInstance().getStore()->getDataStore(Core::Store::Type::Game);
    }

    void GameState::onUpdate(float deltaTime)
    {
        if (_gameDataStore->getBool("chipMoves")) {
            _gameDataStore->setBool("chipMoves", false);
            _gameDataStore->setBool("playerControl", !_gameDataStore->getBool("playerControl"));
        }

        if (_gameDataStore->getBool("win")) {
            // Transition to win state
        } else if (_gameDataStore->getBool("lose")) {
            // Transition to lose state
        }
    }
}
