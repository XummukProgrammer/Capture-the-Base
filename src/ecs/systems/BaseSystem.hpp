#ifndef __BASE_SYSTEM_INCLUDE_FILE__
#define __BASE_SYSTEM_INCLUDE_FILE__

#include "System.hpp"

namespace ECS
{
    class BaseSystem final : public System
    {
    public:
        BaseSystem() = default;
        ~BaseSystem() = default;

    public:
        void onUpdate(float deltaTime, entt::registry& registry) override;
    };
}

#endif // __BASE_SYSTEM_INCLUDE_FILE__
