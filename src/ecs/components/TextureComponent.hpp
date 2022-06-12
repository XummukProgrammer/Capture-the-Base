#ifndef __TEXTURE_COMPONENT_INCLUDE_FILE__
#define __TEXTURE_COMPONENT_INCLUDE_FILE__

#include <SFML/Graphics.hpp>

#include <string>

namespace ECS
{
    struct TextureComponent
    {
        std::string assetId;
        sf::IntRect rectangle;
    };
}

#endif // __TEXTURE_COMPONENT_INCLUDE_FILE__
