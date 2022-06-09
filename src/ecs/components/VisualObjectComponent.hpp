#ifndef __VISUAL_OBJECT_COMPONENT_INCLUDE_FILE__
#define __VISUAL_OBJECT_COMPONENT_INCLUDE_FILE__

#include <core/VisualObject.hpp>

#include <memory>

namespace ECS
{
    struct VisualObjectComponent
    {
        using VisualObjectPtr = std::shared_ptr<Core::VisualObject>;

        // Visual object pointer
        VisualObjectPtr visualObjectPtr;
    };
}

#endif // __VISUAL_OBJECT_COMPONENT_INCLUDE_FILE__
