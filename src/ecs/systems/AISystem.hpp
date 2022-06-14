#ifndef __AI_SYSTEM_INCLUDE_FILE__
#define __AI_SYSTEM_INCLUDE_FILE__

#include "System.hpp"

namespace ECS
{
    class AISystem final : public System
    {
    public:
        AISystem() = default;
        ~AISystem() = default;

    public:
        void onUpdate(float deltaTime, entt::registry& registry) override;
    };
}

#endif // __AI_SYSTEM_INCLUDE_FILE__
