#include "RenderVisualObjects.hpp"

namespace Core
{
    void RenderVisualObjects::addVisualObject(const VisualObjectPtr& visualObjectPtr, int layerId)
    {
        _layers[layerId].push_back(visualObjectPtr);
        visualObjectPtr->setCasheLayerId(layerId);
    }

    void RenderVisualObjects::moveVisualObject(const VisualObjectPtr& visualObjectPtr, int newLayerId)
    {
        removeVisualObject(visualObjectPtr);
        addVisualObject(visualObjectPtr, newLayerId);
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
