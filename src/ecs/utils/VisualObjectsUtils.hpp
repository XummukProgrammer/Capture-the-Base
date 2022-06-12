#ifndef __VISUAL_OBJECTS_UTILS_INCLUDE_FILE__
#define __VISUAL_OBJECTS_UTILS_INCLUDE_FILE__

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <optional>

namespace ECS
{
    class VisualObjectsUtils final
    {
    public:
        struct VisualObjectCreateInfo
        {
            std::string layerName = "Default";
            sf::Vector2f position = { 0.f, 0.f };
            sf::Vector2f scale = { 1.f, 1.f };
            float rotation = 0.f;
            bool isVisible = true;
        };

        struct VisualObjectTextureInfo
        {
            std::optional<std::string> assetId;
            std::optional<sf::IntRect> rectangle;
        };

        static entt::entity create(const VisualObjectCreateInfo& objectInfo, const VisualObjectTextureInfo& textureInfo);
        static void move(entt::entity entity, int newLayerId);
        static void remove(entt::entity entity);
        static void show(entt::entity entity);
        static void hide(entt::entity entity);
        static void updateTexture(entt::entity entity, const VisualObjectTextureInfo& info);
    };
}

#endif // __VISUAL_OBJECTS_UTILS_INCLUDE_FILE__
