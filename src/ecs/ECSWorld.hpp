#ifndef __ECS_WORLD_INCLUDE_FILE__
#define __ECS_WORLD_INCLUDE_FILE__

#include <entt/entt.hpp>

namespace ECS
{
    class World final
    {
    public:
        World() = default;
        ~World() = default;

    public:
        entt::registry& getRegistry();

    private:
        entt::registry _registry;
    };
}

#endif // __ECS_WORLD_INCLUDE_FILE__
