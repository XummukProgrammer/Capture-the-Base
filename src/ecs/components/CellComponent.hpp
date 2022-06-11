#ifndef __CELL_COMPONENT_INCLUDE_FILE__
#define __CELL_COMPONENT_INCLUDE_FILE__

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

namespace ECS
{
    struct CellComponent
    {
        enum class Type
        {
            Black, White
        };
        Type type;

        entt::entity outlineEntity;

        sf::Vector2i indexes;
    };
}

#endif // __CELL_COMPONENT_INCLUDE_FILE__
