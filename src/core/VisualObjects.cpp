#include "VisualObjects.hpp"

#include <core/Application.hpp>
#include <core/Assets.hpp>

namespace Core
{
    void VisualObjects::add(const VisualObjectPtr& visualObjectPtr, int layerId)
    {
        _layers[layerId].push_back(visualObjectPtr);
        visualObjectPtr->setCasheLayerId(layerId);
    }

    void VisualObjects::add(const VisualObjectPtr& visualObjectPtr, const std::string& layerName)
    {
        add(visualObjectPtr, getLayerIdFromName(layerName));
    }

    void VisualObjects::move(const VisualObjectPtr& visualObjectPtr, int newLayerId)
    {
        remove(visualObjectPtr);
        add(visualObjectPtr, newLayerId);
    }

    void VisualObjects::move(const VisualObjectPtr& visualObjectPtr, const std::string& layerName)
    {
        move(visualObjectPtr, getLayerIdFromName(layerName));
    }

    void VisualObjects::moveUp(const VisualObjectPtr& visualObjectPtr)
    {
        const int casheLayerId = visualObjectPtr->getCasheLayerId();
        move(visualObjectPtr, casheLayerId + 1);
    }

    void VisualObjects::moveDown(const VisualObjectPtr& visualObjectPtr)
    {
        const int casheLayerId = visualObjectPtr->getCasheLayerId();
        move(visualObjectPtr, casheLayerId - 1);
    }

    void VisualObjects::remove(const VisualObjectPtr& visualObjectPtr)
    {
        const int casheLayerId = visualObjectPtr->getCasheLayerId();
        auto layerIt = _layers.find(casheLayerId);
        if (layerIt != _layers.end()) {
            auto& visualObjects = layerIt->second;
            for (auto it = visualObjects.begin(); it != visualObjects.end(); ++it) {
                auto& visualObject = *it;
                if (visualObject == visualObjectPtr) {
                    visualObjects.erase(it);
                    return;
                }
            }
        }
    }

    int VisualObjects::getLayerIdFromName(const std::string& layerName)
    {
        if (auto asset = Application::getInstance().getAssets()->getOriginAsset<AssetRenderLayers>("RenderLayers")) {
            return asset->getLayerIdFromName(layerName);
        }
        return 0;
    }

    void VisualObjects::onUpdate(float deltaTime)
    {
    }

    void VisualObjects::onDraw(sf::RenderWindow* wndPtr)
    {
        for (const auto& [ layerId, visualObjects ] : _layers) {
            for (const auto& visualObjectPtr : visualObjects) {
                visualObjectPtr->onDraw(wndPtr);
            }
        }
    }
}
