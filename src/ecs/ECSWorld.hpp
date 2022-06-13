#ifndef __ECS_WORLD_INCLUDE_FILE__
#define __ECS_WORLD_INCLUDE_FILE__

#include <ecs/systems/Systems.hpp>

#include <entt/entt.hpp>

namespace ECS
{
    class World final
    {
    public:
        World() = default;
        ~World() = default;

    public:
        void create();
        void destroy();

        entt::registry& getRegistry();

        template<typename T> void addSystem();

    public:
        void onUpdate(float deltaTime);
        void onDraw(sf::RenderWindow* wndPtr);
        void onEvent(sf::Event* eventPtr);

    private:
        entt::registry _registry;
        Systems* _systemsPtr = nullptr;
    };

    template<typename T>
    void World::addSystem()
    {
        auto newSystem = std::make_unique<T>();
        _systemsPtr->addSystem(std::move(newSystem));
    }
}

#endif // __ECS_WORLD_INCLUDE_FILE__
