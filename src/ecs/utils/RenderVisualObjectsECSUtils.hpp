#ifndef __RENDER_VISUAL_OBJECTS_ECS_UTILS_INCLUDE_FILE__
#define __RENDER_VISUAL_OBJECTS_ECS_UTILS_INCLUDE_FILE__

#include <entt/entt.hpp>

namespace ECS
{
    class RenderVisualObjectsECSUtils final
    {
    public:
        static entt::entity createVisualObject(std::string_view assetId, int layerId = 0);
        static void moveVisualObject(entt::entity entity, int newLayerId);
        static void moveUpVisualObject(entt::entity entity);
        static void moveDownVisualObject(entt::entity entity);
        static void removeVisualObject(entt::entity entity);

    };
}

#endif // __RENDER_VISUAL_OBJECTS_ECS_UTILS_INCLUDE_FILE__
