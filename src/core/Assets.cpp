#include "Assets.hpp"

namespace Core
{
    void Assets::addAsset(std::string_view id, AssetPtr&& asset)
    {
        _assets.emplace(std::string{id}, std::move(asset));
    }
}
