#ifndef __CHIPS_UTILS_INCLUDE_FILE__
#define __CHIPS_UTILS_INCLUDE_FILE__

#include <ecs/components/ChipComponent.hpp>

#include <entt/entt.hpp>

#include <string>

namespace ECS
{
    class ChipsUtils final
    {
    public:
        static entt::entity createChip(ChipComponent::Type type, const sf::Vector2i& indexes, 
            const std::string& textureAssetId, const sf::Vector2i& size);
    };
}

#endif // __CHIPS_UTILS_INCLUDE_FILE__
