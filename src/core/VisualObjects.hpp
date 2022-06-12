#ifndef __VISUAL_OBJECTS_INCLUDE_FILE__
#define __VISUAL_OBJECTS_INCLUDE_FILE__

#include "VisualObject.hpp"

#include <memory>
#include <map>
#include <vector>
#include <string>

namespace Core
{
    class VisualObjects final
    {
    public:
        using VisualObjectPtr = std::shared_ptr<VisualObject>;

    public:
        VisualObjects() = default;
        ~VisualObjects() = default;

    public:
        void add(const VisualObjectPtr& visualObjectPtr, int layerId = 0);
        void add(const VisualObjectPtr& visualObjectPtr, const std::string& layerName = "Default");
        void move(const VisualObjectPtr& visualObjectPtr, int newLayerId = 0);
        void move(const VisualObjectPtr& visualObjectPtr, const std::string& layerName = "Default");
        void moveUp(const VisualObjectPtr& visualObjectPtr);
        void moveDown(const VisualObjectPtr& visualObjectPtr);
        void remove(const VisualObjectPtr& visualObjectPtr);

    private:
        int getLayerIdFromName(const std::string& layerName);

    public:
        void onUpdate(float deltaTime);
        void onDraw(sf::RenderWindow* wndPtr);

    private:
        std::map<int, std::vector<VisualObjectPtr>> _layers;

    };
}

#endif // __VISUAL_OBJECTS_INCLUDE_FILE__
