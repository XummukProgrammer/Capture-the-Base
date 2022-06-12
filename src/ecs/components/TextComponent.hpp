#ifndef __TEXT_COMPONENT_INCLUDE_FILE__
#define __TEXT_COMPONENT_INCLUDE_FILE__

#include <SFML/Graphics.hpp>

#include <string>

namespace ECS
{
    struct TextComponent
    {
        sf::Text object;
        bool isVisible = true;

        std::string fontAssetId;
        std::string text;
        unsigned size;
        sf::Color color;
        sf::Uint32 style;
    };

    struct UpdateTextComponent
    {
        bool _;
    };
}

#endif // __TEXT_COMPONENT_INCLUDE_FILE__
