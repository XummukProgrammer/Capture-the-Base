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
        void setCasheLayerId(int layerId);
        int getCasheLayerId() const;

        void show();
        void hide();
        bool isVisible() const;

        void loadFromAsset(std::string_view assetId);

        sf::Sprite& getSprite();

    public:
        void onDraw(sf::RenderWindow* wndPtr);

    private:
        sf::Sprite _sprite;
        int _casheLayerId = 0;
        bool _isVisible = true;
    };
}

#endif // __VISUAL_OBJECT_INCLUDE_FILE__
