#ifndef __ECS_FACTORY_OBJECTS_INCLUDE_FILE__
#define __ECS_FACTORY_OBJECTS_INCLUDE_FILE__

#include <entt/entt.hpp>

#include <string>

namespace ECS
{
    entt::entity createVisualObject(std::string_view assetId, int layerId = 0);
}

#endif // __ECS_FACTORY_OBJECTS_INCLUDE_FILE__
