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

    void VisualObject::show()
    {
        _isVisible = true;
    }

    void VisualObject::hide()
    {
        _isVisible = false;
    }

    bool VisualObject::isVisible() const
    {
        return _isVisible;
    }

    void VisualObject::loadFromAsset(std::string_view assetId)
    {
        if (_assetId == assetId) {
            return;
        }

        _assetId = assetId;

        if (auto asset = Application::getInstance().getAssets()->getAsset<AssetTexture>(assetId)) {
            _sprite.setTexture(*asset);
        }
    }

    sf::Sprite& VisualObject::getSprite()
    {
        return _sprite;
    }

    void VisualObject::onDraw(sf::RenderWindow* wndPtr)
    {
        if (isVisible()) {
            wndPtr->draw(_sprite);
        }
    }
}
