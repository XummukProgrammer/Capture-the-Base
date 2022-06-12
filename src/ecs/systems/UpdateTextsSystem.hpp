#ifndef __UPDATE_TEXTS_SYSTEM_INCLUDE_FILE__
#define __UPDATE_TEXTS_SYSTEM_INCLUDE_FILE__

#include "System.hpp"

namespace ECS
{
    class UpdateTextsSystem final : public System
    {
    public:
        UpdateTextsSystem() = default;
        ~UpdateTextsSystem() = default;

    public:
        void onUpdate(float deltaTime, entt::registry& registry) override;
        void onDraw(entt::registry& registry, sf::RenderWindow* wndPtr) override;
    };
}

#endif // __UPDATE_TEXTS_SYSTEM_INCLUDE_FILE__
