#ifndef __SYSTEM_INCLUDE_FILE__
#define __SYSTEM_INCLUDE_FILE__

#include <entt/entt.hpp>

namespace ECS
{
    class System
    {
    public:
        System() = default;
        virtual ~System() = default;

    public:
        virtual void onUpdate(float deltaTime, entt::registry& registry) {}
    };
}

#endif // __SYSTEM_INCLUDE_FILE__
