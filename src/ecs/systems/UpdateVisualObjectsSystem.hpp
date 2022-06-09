#ifndef __UPDATE_VISUAL_OBJECTS_SYSTEM_INCLUDE_FILE__
#define __UPDATE_VISUAL_OBJECTS_SYSTEM_INCLUDE_FILE__

#include "System.hpp"

namespace ECS
{
    class UpdateVisualObjectsSystem final : public System
    {
    public:
        UpdateVisualObjectsSystem() = default;
        ~UpdateVisualObjectsSystem() = default;

    public:
        void onUpdate(float deltaTime, entt::registry& registry) override;
    };
}

#endif // __UPDATE_VISUAL_OBJECTS_SYSTEM_INCLUDE_FILE__
