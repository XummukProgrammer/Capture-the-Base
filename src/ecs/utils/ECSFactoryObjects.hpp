#ifndef __ECS_FACTORY_OBJECTS_INCLUDE_FILE__
#define __ECS_FACTORY_OBJECTS_INCLUDE_FILE__

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

#include <string>

namespace ECS
{
    entt::entity createVisualObject(std::string_view assetId, int layerId = 0,
        const sf::Vector2f& position = { 0.f, 0.f },
        const sf::Vector2f& scale = { 1.f, 1.f },
        float rotation = 0.f);
}

#endif // __ECS_FACTORY_OBJECTS_INCLUDE_FILE__
