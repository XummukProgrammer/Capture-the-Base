#ifndef __SYSTEM_INCLUDE_FILE__
#define __SYSTEM_INCLUDE_FILE__

#include <SFML/Graphics.hpp>

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
        virtual void onDraw(entt::registry& registry, sf::RenderWindow* wndPtr) {}
        virtual void onEvent(entt::registry& registry, sf::Event* eventPtr) {}
    };
}

#endif // __SYSTEM_INCLUDE_FILE__
