#include "Asset.hpp"

namespace Core
{
    void AssetTexture::loadFromFile(std::string_view filePath)
    {
        auto dataPtr = std::make_unique<sf::Texture>();
        dataPtr->loadFromFile(std::string{filePath});
        setData(std::move(dataPtr));
    }
}
