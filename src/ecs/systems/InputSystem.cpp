#include "InputSystem.hpp"

#include <ecs/utils/PlayerUtils.hpp>

#include <SFML/Graphics.hpp>

namespace ECS
{
    void InputSystem::onEvent(entt::registry& registry, sf::Event* eventPtr)
    {
        if (eventPtr->type == sf::Event::MouseButtonPressed) {
            if (eventPtr->mouseButton.button == sf::Mouse::Left) {
                PlayerUtils::trySetTargetChip();
                PlayerUtils::tryMoveTargetChip();
            }
        }
    }
}
