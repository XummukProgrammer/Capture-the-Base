#ifndef __BASE_UTILS_INCLUDE_FILE__
#define __BASE_UTILS_INCLUDE_FILE__

#include <ecs/components/ChipComponent.hpp>

#include <entt/entt.hpp>

namespace ECS
{
    class BaseUtils final
    {
    public:
        static void setBase(entt::entity entity, ChipComponent::Type type);
        static void unsetBase(entt::entity entity);

        static bool isBaseCaptured(ChipComponent::Type type);
    };
}

#endif // __BASE_UTILS_INCLUDE_FILE__
