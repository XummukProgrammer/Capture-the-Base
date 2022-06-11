#ifndef __ASSETS_INCLUDE_FILE__
#define __ASSETS_INCLUDE_FILE__

#include "Asset.hpp"

#include <memory>
#include <map>
#include <string>
#include <iostream>

namespace Core
{
    class Assets final
    {
    public:
        using AssetPtr = std::shared_ptr<Asset>;

    public:
        Assets() = default;
        ~Assets() = default;

    public:
        void loadFromFile(std::string_view filePath);

        void addAsset(std::string_view id, AssetPtr&& asset);
        template<typename T> typename T::OriginType* getAsset(std::string_view id) const;
        template<typename T> std::shared_ptr<T> getOriginAsset(std::string_view id) const;

    private:
        std::map<std::string, AssetPtr> _assets;
    };

    template<typename T>
    typename T::OriginType* Assets::getAsset(std::string_view id) const
    {
        auto it = _assets.find(std::string{id});
        if (it != _assets.end()) {
            if (auto castedAsset = std::dynamic_pointer_cast<T>(it->second)) {
                return castedAsset->getData();
            }
        }
        return nullptr;
    }
    template<typename T>
    std::shared_ptr<T> Assets::getOriginAsset(std::string_view id) const
    {
        auto it = _assets.find(std::string{id});
        if (it != _assets.end()) {
            return std::dynamic_pointer_cast<T>(it->second);
        }
        return nullptr;
    }
}

#endif // __ASSETS_INCLUDE_FILE__
