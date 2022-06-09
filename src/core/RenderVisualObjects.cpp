#include "RenderVisualObjects.hpp"

namespace Core
{
    void RenderVisualObjects::addVisualObject(const VisualObjectPtr& visualObjectPtr)
    {
        _visualObjects.push_back(visualObjectPtr);
    }

    void RenderVisualObjects::onUpdate(float deltaTime)
    {
    }

    void RenderVisualObjects::onDraw(sf::RenderWindow* wndPtr)
    {
        for (const auto& visualObjectPtr : _visualObjects) {
            visualObjectPtr->onDraw(wndPtr);
        }
    }
}
