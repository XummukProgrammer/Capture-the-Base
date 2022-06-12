#include "TeamsUtils.hpp"

#include "ChipsUtils.hpp"

namespace ECS
{
    void TeamsUtils::createTeam(ChipComponent::Type type, const std::string& textureAssetId, const sf::Vector2i& size, 
        const sf::Vector2i& startIndexes, const sf::Vector2i& blocks)
    {
        const int endX = startIndexes.x + blocks.x;
        const int endY = startIndexes.y + blocks.y;

        for (int y = startIndexes.y; y < endY; ++y) {
            for (int x = startIndexes.x; x < endX; ++x) {
                ChipsUtils::createChip(type, { x, y }, textureAssetId, size);
            }
        }
    }
}
