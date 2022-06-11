#ifndef __ASSET_INCLUDE_FILE__
#define __ASSET_INCLUDE_FILE__

#include "Factory.hpp"

#include <SFML/Graphics.hpp>

#include <pugixml.hpp>

#include <memory>
#include <string>
#include <vector>

namespace Core
{
    class Asset : public Factorable
    {
    public:
        using OriginType = Asset;

    public:
        Asset() = default;
        virtual ~Asset() = default;

    public:
        void setParentFileDir(std::string_view fileDir);
        const std::string& getParentFileDir() const;

    public:
        virtual void loadFromFile(pugi::xml_node& node) = 0;

    private:
        std::string _parentFileDir;
    };

    template<typename T>
    class AssetData : public Asset
    {
    public:
        using OriginType = T;
        using DataPtr = std::unique_ptr<OriginType>;

    public:
        AssetData() = default;
        virtual ~AssetData() = default;

    public:
        void setData(DataPtr&& data);
        OriginType* getData() const;

    private:
        DataPtr _dataPtr;
    };

    template<typename T>
    void AssetData<T>::setData(DataPtr&& data)
    {
        _dataPtr = std::move(data);
    }

    template<typename T>
    typename AssetData<T>::OriginType* AssetData<T>::getData() const
    {
        return _dataPtr.get();
    }

    class AssetTexture final : public AssetData<sf::Texture>
    {
    public:
        AssetTexture() = default;
        ~AssetTexture() = default;

    public:
        void loadFromFile(pugi::xml_node& node) override;
        void loadFromFile(std::string_view filePath);
    };

    class AssetRenderLayers final : public AssetData<std::vector<std::string>>
    {
    public:
        AssetRenderLayers() = default;
        ~AssetRenderLayers() = default;

    public:
        void loadFromFile(pugi::xml_node& node) override;

    public:
        int getLayerIdFromName(std::string_view name) const;
    };
}

#endif // __ASSET_INCLUDE_FILE__
