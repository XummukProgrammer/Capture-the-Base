#ifndef __RENDER_VISUAL_OBJECTS_ECS_UTILS_INCLUDE_FILE__
#define __RENDER_VISUAL_OBJECTS_ECS_UTILS_INCLUDE_FILE__

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

#include <string>

namespace ECS
{
    class RenderVisualObjectsECSUtils final
    {
    public:
        struct VisualObjectCreateInfo
        {
            std::string assetId;
            std::string layerName = "Default";
            sf::Vector2f position = { 0.f, 0.f };
            sf::Vector2f scale = { 1.f, 1.f };
            float rotation = 0.f;
            sf::IntRect textureRect = { 0, 0, 32, 32 };
            bool isVisible = true;
        };

        static entt::entity createVisualObject(const VisualObjectCreateInfo& info);
        static void moveVisualObject(entt::entity entity, int newLayerId);
        static void moveUpVisualObject(entt::entity entity);
        static void moveDownVisualObject(entt::entity entity);
        static void removeVisualObject(entt::entity entity);
        static void showVisualObject(entt::entity entity);
        static void hideVisualObject(entt::entity entity);

    };
}

#endif // __RENDER_VISUAL_OBJECTS_ECS_UTILS_INCLUDE_FILE__
