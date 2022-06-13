#ifndef __CHIP_COMPONENT_INCLUDE_FILE__
#define __CHIP_COMPONENT_INCLUDE_FILE__

#include <SFML/Graphics.hpp>

namespace ECS
{
    struct ChipComponent
    {
        enum class Type
        {
            White,
            Black
        };
        Type type;

        sf::Vector2i indexes;
    };

    struct ChipTargetComponent
    {
        bool _;
    };
}

#endif // __CHIP_COMPONENT_INCLUDE_FILE__
