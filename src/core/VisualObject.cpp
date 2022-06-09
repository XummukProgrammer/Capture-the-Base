#include "VisualObject.hpp"

#include "Application.hpp"
#include "Assets.hpp"

namespace Core
{
    void VisualObject::setCasheLayerId(int layerId)
    {
        _casheLayerId = layerId;
    }

    int VisualObject::getCasheLayerId() const
    {
        return _casheLayerId;
    }

    void VisualObject::loadFromAsset(std::string_view assetId)
    {
        if (auto asset = Application::getInstance().getAssets()->getAsset<AssetTexture>(assetId)) {
            _sprite.setTexture(*asset);
            _sprite.setTextureRect({ 0, 0, 32, 32 });
        }
    }

    sf::Sprite& VisualObject::getSprite()
    {
        return _sprite;
    }

    void VisualObject::onDraw(sf::RenderWindow* wndPtr)
    {
        wndPtr->draw(_sprite);
    }
}
