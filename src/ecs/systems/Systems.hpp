#ifndef __SYSTEMS_INCLUDE_FILE__
#define __SYSTEMS_INCLUDE_FILE__

#include "System.hpp"

#include <memory>
#include <list>

namespace ECS
{
    class Systems final
    {
    public:
        using SystemPtr = std::unique_ptr<System>;

    public:
        Systems() = default;
        ~Systems() = default;

    public:
        void addSystem(SystemPtr&& systemPtr);

        void onUpdate(float deltaTime);
        void onDraw(sf::RenderWindow* wndPtr);
        void onEvent(sf::Event* eventPtr);

    private:
        std::list<SystemPtr> _systems;
    };
}

#endif // __SYSTEMS_INCLUDE_FILE__
