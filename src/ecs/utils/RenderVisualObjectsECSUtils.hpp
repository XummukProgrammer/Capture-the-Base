#ifndef __RENDER_VISUAL_OBJECTS_ECS_UTILS_INCLUDE_FILE__
#define __RENDER_VISUAL_OBJECTS_ECS_UTILS_INCLUDE_FILE__

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

#include <string>
#include <optional>

namespace ECS
{
    class RenderVisualObjectsECSUtils final
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

        static entt::entity create(const VisualObjectCreateInfo& info);
        static void move(entt::entity entity, int newLayerId);
        static void moveUp(entt::entity entity);
        static void moveDown(entt::entity entity);
        static void remove(entt::entity entity);
        static void show(entt::entity entity);
        static void hide(entt::entity entity);
        static void setTexture(entt::entity entity, const VisualObjectTextureInfo& info);

    };
}

#endif // __RENDER_VISUAL_OBJECTS_ECS_UTILS_INCLUDE_FILE__
