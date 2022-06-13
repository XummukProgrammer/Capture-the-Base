#include "InputSystem.hpp"

#include <core/Application.hpp>
#include <core/Store.hpp>

#include <ecs/utils/PlayerUtils.hpp>

#include <SFML/Graphics.hpp>

namespace ECS
{
    void InputSystem::onEvent(entt::registry& registry, sf::Event* eventPtr)
    {
        if (auto dataStore = Core::Application::getInstance().getStore()->getDataStore(Core::Store::Type::Game)) {
            if (!dataStore->getBool("playerControl")) {
                return;
            }
        }

        if (eventPtr->type == sf::Event::MouseButtonPressed) {
            if (eventPtr->mouseButton.button == sf::Mouse::Left) {
                PlayerUtils::trySetTargetChip();
                PlayerUtils::tryMoveTargetChip();
            }
        }
    }
}
