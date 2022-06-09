#ifndef __RENDER_VISUAL_OBJECTS_INCLUDE_FILE__
#define __RENDER_VISUAL_OBJECTS_INCLUDE_FILE__

#include "VisualObject.hpp"

#include <memory>
#include <vector>

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
        void addVisualObject(const VisualObjectPtr& visualObjectPtr);

    public:
        void onUpdate(float deltaTime);
        void onDraw(sf::RenderWindow* wndPtr);

    private:
        std::vector<VisualObjectPtr> _visualObjects;

    };
}

#endif // __RENDER_VISUAL_OBJECTS_INCLUDE_FILE__
