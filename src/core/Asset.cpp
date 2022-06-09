#include "Asset.hpp"

#include "Application.hpp"

namespace Core
{
    void Asset::setParentFileDir(std::string_view fileDir)
    {
        _parentFileDir = fileDir;
    }

    const std::string& Asset::getParentFileDir() const
    {
        return _parentFileDir;
    }

    void AssetTexture::loadFromFile(pugi::xml_node& node)
    {
        const std::string filePath = getParentFileDir() + "\\" + node.attribute("filePath").as_string();

        loadFromFile(filePath);
    }

    void AssetTexture::loadFromFile(std::string_view filePath)
    {
        auto dataPtr = std::make_unique<sf::Texture>();
        dataPtr->loadFromFile(std::string{filePath});
        setData(std::move(dataPtr));
    }
}
