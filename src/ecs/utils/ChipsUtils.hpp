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
            const std::string& textureAssetId, const sf::Vector2i& size, bool isEnemy);
        static entt::entity getChipFromIndexes(const sf::Vector2i& indexes);

        static void setTargetChip(entt::entity entity);
        static void unsetTargetChip(entt::entity entity);
        static void unsetTargetChip();
        static entt::entity getTargetChip();

        static void moveChip(entt::entity entity, const sf::Vector2i& newIndexes);

        static ChipComponent::Type reverseType(ChipComponent::Type type);
    };
}

#endif // __CHIPS_UTILS_INCLUDE_FILE__
