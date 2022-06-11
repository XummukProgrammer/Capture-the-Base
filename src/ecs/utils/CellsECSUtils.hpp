#ifndef __CELLS_ECS_UTILS_INCLUDE_FILE__
#define __CELLS_ECS_UTILS_INCLUDE_FILE__

#include <ecs/components/CellComponent.hpp>

#include <string>
#include <tuple>

namespace ECS
{
    class CellsECSUtils final
    {
    public:
        static entt::entity createCell(const sf::Vector2f& startPosition, CellComponent::Type type, const sf::Vector2i& indexes,
            const std::string& cellTextureAssetId, const std::string& outlineTextureAssetId, const sf::Vector2i& size);
        static std::tuple<entt::entity, entt::entity> createCellsBlock(const sf::Vector2f& startPosition, 
            CellComponent::Type startType, const sf::Vector2i& indexes,
            const std::string& whiteCellTextureAssetId, const std::string& whiteOutlineTextureAssetId,
            const std::string& blackCellTextureAssetId, const std::string& blackOutlineTextureAssetId,
            const sf::Vector2i& size);
        static void createCells(const sf::Vector2f& startPosition, const sf::Vector2i& blocks, 
            const std::string& whiteCellTextureAssetId, const std::string& whiteOutlineTextureAssetId, 
            const std::string& blackCellTextureAssetId, const std::string& blackOutlineTextureAssetId,
            const sf::Vector2i& size);
    };
}

#endif // __CELLS_ECS_UTILS_INCLUDE_FILE__
