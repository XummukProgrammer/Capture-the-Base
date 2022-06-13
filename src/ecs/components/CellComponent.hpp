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

        entt::entity outlineTopEntity = entt::null;
        entt::entity outlineDownEntity = entt::null;
        entt::entity outlineLeftEntity = entt::null;
        entt::entity outlineRightEntity = entt::null;

        entt::entity moveableEntity = entt::null;
        entt::entity selectedEntity = entt::null;

        entt::entity textTopEntity = entt::null;
        entt::entity textDownEntity = entt::null;
        entt::entity textLeftEntity = entt::null;
        entt::entity textRightEntity = entt::null;

        sf::Vector2i indexes;
    };

    struct CellMoveableComponent
    {
        bool _;
    };
}

#endif // __CELL_COMPONENT_INCLUDE_FILE__
