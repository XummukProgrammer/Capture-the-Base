#include "Assets.hpp"

#include "Application.hpp"
#include "Factory.hpp"

#include <pugixml.hpp>

namespace Core
{
    void Assets::loadFromFile(std::string_view filePath)
    {
        auto&& path = Application::getInstance().buildPath(filePath);

        pugi::xml_document doc;
        if (!doc.load_file(path.c_str())) {
            return;
        }

        auto assetsNode = doc.first_child();

        for (auto assetNode = assetsNode.child("Asset"); assetNode; assetNode = assetNode.next_sibling("Asset")) {
            const std::string assetType = assetNode.attribute("type").as_string();
            const std::string assetId = assetNode.attribute("id").as_string();

            if (auto&& factorable = Application::getInstance().getFactory()->createType(assetType))
            {
                if (auto asset = std::dynamic_pointer_cast<Asset>(factorable)) {
                    asset->loadFromFile(assetNode);
                    addAsset(assetId, std::move(asset));
                }
            }
        }
    }

    void Assets::addAsset(std::string_view id, AssetPtr&& asset)
    {
        _assets.emplace(std::string{id}, std::move(asset));
    }
}
