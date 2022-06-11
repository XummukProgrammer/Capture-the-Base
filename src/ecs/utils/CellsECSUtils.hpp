#ifndef __CELLS_ECS_UTILS_INCLUDE_FILE__
#define __CELLS_ECS_UTILS_INCLUDE_FILE__

#include <ecs/components/CellComponent.hpp>

#include <string>

namespace ECS
{
    class CellsECSUtils final
    {
    public:
        using TexturesPair = std::pair<std::string, std::string>;
        using TexturesMap = std::map<CellComponent::Type, TexturesPair>;

    public:
        static entt::entity createCell(const sf::Vector2f& startPosition, CellComponent::Type type, const sf::Vector2i& indexes,
            const TexturesPair& texturesPair, const sf::Vector2i& size);
        static void createCellsBlock(const sf::Vector2f& startPosition, 
            CellComponent::Type startType, const sf::Vector2i& indexes, TexturesMap& textures, 
            const sf::Vector2i& size);
        static void createCells(const sf::Vector2f& startPosition, const sf::Vector2i& blocks, 
            const std::string& whiteCellTextureAssetId, const std::string& whiteOutlineTextureAssetId, 
            const std::string& blackCellTextureAssetId, const std::string& blackOutlineTextureAssetId,
            const sf::Vector2i& size);

        static entt::entity getCellFromIndexes(const sf::Vector2i& indexes);
    };
}

#endif // __CELLS_ECS_UTILS_INCLUDE_FILE__
