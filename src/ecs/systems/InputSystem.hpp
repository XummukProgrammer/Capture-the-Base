#ifndef __INPUT_SYSTEM_INCLUDE_FILE__
#define __INPUT_SYSTEM_INCLUDE_FILE__

#include "System.hpp"

namespace ECS
{
    class InputSystem final : public System
    {
    public:
        InputSystem() = default;
        ~InputSystem() = default;

    public:
        void onUpdate(float deltaTime, entt::registry& registry) override;

    private:
        // TODO: Remove on create AI system
        float _mouseClickTimerDelay = 0.f;
    };
}

#endif // __INPUT_SYSTEM_INCLUDE_FILE__
