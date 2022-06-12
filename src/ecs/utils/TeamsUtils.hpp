#ifndef __TEAMS_UTILS_INCLUDE_FILE__
#define __TEAMS_UTILS_INCLUDE_FILE__

#include <ecs/components/ChipComponent.hpp>

namespace ECS
{
    class TeamsUtils final
    {
    public:
        static void createTeam(ChipComponent::Type type, const std::string& textureAssetId, const sf::Vector2i& size, 
            const sf::Vector2i& startIndexes, const sf::Vector2i& blocks);
    };
}

#endif // __TEAMS_UTILS_INCLUDE_FILE__
