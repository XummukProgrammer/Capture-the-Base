#ifndef __CELLS_UTILS_INCLUDE_FILE__
#define __CELLS_UTILS_INCLUDE_FILE__

#include <ecs/components/CellComponent.hpp>

#include <string>
#include <vector>

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

        struct CellFonts
        {
            std::string topFontAssetId;
            std::string downFontAssetId;
            std::string leftFontAssetId;
            std::string rightFontAssetId;
        };

    public:
        static entt::entity createCell(const sf::Vector2f& startPosition, CellComponent::Type type, const sf::Vector2i& indexes,
            const CellTextures& textures, const sf::Vector2i& size, const CellFonts& cellFonts, const sf::Vector2i& maxIndexes);
        static void createCellsBlock(const sf::Vector2f& startPosition, 
            CellComponent::Type startType, const sf::Vector2i& indexes, const CellsTextures& cellsTextures,
            const sf::Vector2i& size, const CellFonts& cellFonts, const sf::Vector2i& maxIndexes);
        static void createCells(const sf::Vector2f& startPosition, const sf::Vector2i& blocks, 
            const CellsTextures& cellsTextures,
            const sf::Vector2i& size, const CellFonts& cellFonts);

        static entt::entity getCellFromIndexes(const sf::Vector2i& indexes);
        static std::vector<entt::entity> getAvailableCellsFromIndexes(const sf::Vector2i& indexes);
        static std::vector<entt::entity> getMoveableCellsFromIndexes(const sf::Vector2i& indexes);

        static void setMoveableCell(entt::entity entity);
        static void unsetMoveableCell(entt::entity entity);
        static void unsetMoveableCells();

    private:
        static std::string getCellTextIndex(int maxY, int cellY);
        static std::string getCellSymbol(int cellX);
    };
}

#endif // __CELLS_UTILS_INCLUDE_FILE__
