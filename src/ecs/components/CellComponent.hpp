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

        entt::entity outlineTopEntity;
        entt::entity outlineDownEntity;
        entt::entity outlineLeftEntity;
        entt::entity outlineRightEntity;
        entt::entity moveableEntity;
        entt::entity selectedEntity;

        sf::Vector2i indexes;
    };
}

#endif // __CELL_COMPONENT_INCLUDE_FILE__
