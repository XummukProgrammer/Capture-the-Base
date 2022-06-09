#ifndef __TRANSFORM_COMPONENT_INCLUDE_FILE__
#define __TRANSFORM_COMPONENT_INCLUDE_FILE__

#include <SFML/Graphics.hpp>

namespace ECS
{
    struct TransformComponent
    {
        // Position
        sf::Vector2f position = { 0.f, 0.f };

        // Scale
        sf::Vector2f scale = { 1.f, 1.f };

        // Rotation
        float rotation = 0.f;
    };
}

#endif // __TRANSFORM_COMPONENT_INCLUDE_FILE__
