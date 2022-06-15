#ifndef __AI_UTILS_INCLUDE_FILE__
#define __AI_UTILS_INCLUDE_FILE__

#include <entt/entt.hpp>

#include <vector>

namespace ECS
{
    class AIUtils final
    {
    public:
        static void setAI(entt::entity entity);
        static void unsetAI(entt::entity entity);

        static void generatePath(entt::entity entity);
        static void generatePaths();

        static void moveFromPath(entt::entity entity);

        static std::vector<entt::entity> getMoveableEntities();
    };
}

#endif // __AI_UTILS_INCLUDE_FILE__
