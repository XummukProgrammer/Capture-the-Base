#ifndef __AI_COMPONENT_INCLUDE_FILE__
#define __AI_COMPONENT_INCLUDE_FILE__

#include <entt/entt.hpp>
#include <SFML/System/Vector2.hpp>

#include <queue>

namespace ECS
{
    struct AIComponent
    {
        std::queue<sf::Vector2i> pathQueue;
    };
}

#endif // __AI_COMPONENT_INCLUDE_FILE__
