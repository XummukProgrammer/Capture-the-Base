#ifndef __TEXTS_UTILS_INCLUDE_FILE__
#define __TEXTS_UTILS_INCLUDE_FILE__

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

namespace ECS
{
    class TextsUtils final
    {
    public:
        struct TextCreateInfo
        {
            std::string fontAssetId;
            std::string text;
            unsigned size = 20;
            sf::Color color = sf::Color::Black;
            sf::Uint32 style;
            sf::Vector2f position = { 0.f, 0.f };
            sf::Vector2f scale = { 1.f, 1.f };
            float rotation = 0.f;
            bool isVisible = true;
        };

    public:
        static entt::entity createText(const TextCreateInfo& info);
        static void updateText(entt::entity entity, const TextCreateInfo& info);
        static void showText(entt::entity entity, const std::string& text = "");
        static void hideText(entt::entity entity);
    };
}

#endif // __TEXTS_UTILS_INCLUDE_FILE__
