#ifndef __RENDER_VISUAL_OBJECTS_INCLUDE_FILE__
#define __RENDER_VISUAL_OBJECTS_INCLUDE_FILE__

#include "VisualObject.hpp"

#include <memory>
#include <map>
#include <vector>
#include <string>

namespace Core
{
    class RenderVisualObjects final
    {
    public:
        using VisualObjectPtr = std::shared_ptr<VisualObject>;

    public:
        RenderVisualObjects() = default;
        ~RenderVisualObjects() = default;

    public:
        void addVisualObject(const VisualObjectPtr& visualObjectPtr, int layerId = 0);
        void addVisualObject(const VisualObjectPtr& visualObjectPtr, const std::string& layerName = "Default");
        void moveVisualObject(const VisualObjectPtr& visualObjectPtr, int newLayerId = 0);
        void moveVisualObject(const VisualObjectPtr& visualObjectPtr, const std::string& layerName = "Default");
        void moveUpVisualObject(const VisualObjectPtr& visualObjectPtr);
        void moveDownVisualObject(const VisualObjectPtr& visualObjectPtr);
        void removeVisualObject(const VisualObjectPtr& visualObjectPtr);

    private:
        int getLayerIdFromName(const std::string& layerName);

    public:
        void onUpdate(float deltaTime);
        void onDraw(sf::RenderWindow* wndPtr);

    private:
        std::map<int, std::vector<VisualObjectPtr>> _layers;

    };
}

#endif // __RENDER_VISUAL_OBJECTS_INCLUDE_FILE__
