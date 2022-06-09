#ifndef __VISUAL_OBJECT_INCLUDE_FILE__
#define __VISUAL_OBJECT_INCLUDE_FILE__

#include <SFML/Graphics.hpp>

#include <string>

namespace Core
{
    class VisualObject final
    {
    public:
        VisualObject() = default;
        ~VisualObject() = default;

    public:
        void loadFromAsset(std::string_view assetId);

        sf::Sprite& getSprite();

    public:
        void onDraw(sf::RenderWindow* wndPtr);

    private:
        sf::Sprite _sprite;
    };
}

#endif // __VISUAL_OBJECT_INCLUDE_FILE__
