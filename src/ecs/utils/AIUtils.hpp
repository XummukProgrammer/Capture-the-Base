#ifndef __AI_UTILS_INCLUDE_FILE__
#define __AI_UTILS_INCLUDE_FILE__

#include <entt/entt.hpp>

namespace ECS
{
    class AIUtils final
    {
    public:
        static void setAI(entt::entity entity);
        static void unsetAI(entt::entity entity);

        static void generatePath(entt::entity entity);

        static void moveFromPath(entt::entity entity);
    };
}

#endif // __AI_UTILS_INCLUDE_FILE__
