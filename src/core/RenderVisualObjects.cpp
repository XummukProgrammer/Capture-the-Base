#include "RenderVisualObjects.hpp"

#include <core/Application.hpp>
#include <core/Assets.hpp>

namespace Core
{
    void RenderVisualObjects::addVisualObject(const VisualObjectPtr& visualObjectPtr, int layerId)
    {
        _layers[layerId].push_back(visualObjectPtr);
        visualObjectPtr->setCasheLayerId(layerId);
    }

    void RenderVisualObjects::addVisualObject(const VisualObjectPtr& visualObjectPtr, const std::string& layerName)
    {
        addVisualObject(visualObjectPtr, getLayerIdFromName(layerName));
    }

    void RenderVisualObjects::moveVisualObject(const VisualObjectPtr& visualObjectPtr, int newLayerId)
    {
        removeVisualObject(visualObjectPtr);
        addVisualObject(visualObjectPtr, newLayerId);
    }

    void RenderVisualObjects::moveVisualObject(const VisualObjectPtr& visualObjectPtr, const std::string& layerName)
    {
        moveVisualObject(visualObjectPtr, getLayerIdFromName(layerName));
    }

    void RenderVisualObjects::moveUpVisualObject(const VisualObjectPtr& visualObjectPtr)
    {
        const int casheLayerId = visualObjectPtr->getCasheLayerId();
        moveVisualObject(visualObjectPtr, casheLayerId + 1);
    }

    void RenderVisualObjects::moveDownVisualObject(const VisualObjectPtr& visualObjectPtr)
    {
        const int casheLayerId = visualObjectPtr->getCasheLayerId();
        moveVisualObject(visualObjectPtr, casheLayerId - 1);
    }

    void RenderVisualObjects::removeVisualObject(const VisualObjectPtr& visualObjectPtr)
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

    int RenderVisualObjects::getLayerIdFromName(const std::string& layerName)
    {
        if (auto asset = Application::getInstance().getAssets()->getOriginAsset<AssetRenderLayers>("RenderLayers")) {
            return asset->getLayerIdFromName(layerName);
        }
        return 0;
    }

    void RenderVisualObjects::onUpdate(float deltaTime)
    {
    }

    void RenderVisualObjects::onDraw(sf::RenderWindow* wndPtr)
    {
        for (const auto& [ layerId, visualObjects ] : _layers) {
            for (const auto& visualObjectPtr : visualObjects) {
                visualObjectPtr->onDraw(wndPtr);
            }
        }
    }
}
