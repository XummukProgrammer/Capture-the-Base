#ifndef __CELLS_UTILS_INCLUDE_FILE__
#define __CELLS_UTILS_INCLUDE_FILE__

#include <ecs/components/CellComponent.hpp>

#include <string>

namespace ECS
{
    class CellsUtils final
    {
    public:
        struct CellTextures
        {
            std::string baseAssetId;
            std::string outlineTopAssetId;
            std::string outlineDownAssetId;
            std::string outlineLeftAssetId;
            std::string outlineRightAssetId;
            std::string moveableAssetId;
            std::string selectedAssetId;
        };

        struct CellsTextures
        {
            CellTextures whiteCellTextures;
            CellTextures blackCellTextures;
        };

    public:
        static entt::entity createCell(const sf::Vector2f& startPosition, CellComponent::Type type, const sf::Vector2i& indexes,
            const CellTextures& textures, const sf::Vector2i& size);
        static void createCellsBlock(const sf::Vector2f& startPosition, 
            CellComponent::Type startType, const sf::Vector2i& indexes, const CellsTextures& cellsTextures,
            const sf::Vector2i& size);
        static void createCells(const sf::Vector2f& startPosition, const sf::Vector2i& blocks, 
            const CellsTextures& cellsTextures,
            const sf::Vector2i& size);

        static entt::entity getCellFromIndexes(const sf::Vector2i& indexes);
    };
}

#endif // __CELLS_UTILS_INCLUDE_FILE__
