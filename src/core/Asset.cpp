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

    void AssetRenderLayers::loadFromFile(pugi::xml_node& node)
    {
        auto dataPtr = std::make_unique<std::vector<std::string>>();
        for (auto layerNode = node.child("Layer"); layerNode; layerNode = layerNode.next_sibling("Layer")) {
            const std::string& id = layerNode.attribute("id").as_string();
            dataPtr->push_back(id);
        }
        dataPtr->push_back("Default");
        setData(std::move(dataPtr));
    }

    int AssetRenderLayers::getLayerIdFromName(std::string_view name) const
    {
        const auto& data = *getData();
        auto it = std::find(data.begin(), data.end(), std::string{name});
        if (it != data.end()) {
            return static_cast<int>(std::distance(data.begin(), it));
        }
        return 0;
    }
}
