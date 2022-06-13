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
        void onEvent(entt::registry& registry, sf::Event* eventPtr) override;
    };
}

#endif // __INPUT_SYSTEM_INCLUDE_FILE__
