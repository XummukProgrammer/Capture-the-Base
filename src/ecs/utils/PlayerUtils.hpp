#ifndef __PLAYER_UTILS_INCLUDE_FILE__
#define __PLAYER_UTILS_INCLUDE_FILE__

#include <ecs/components/VisualObjectComponent.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

namespace ECS
{
    class PlayerUtils final
    {
    public:
        static void trySetTargetChip();
        static void tryMoveTargetChip();

    private:
        static sf::Vector2f getMousePosition();
        static bool isContainsWithMousePosition(const VisualObjectComponent& visualObjectComponent);
    };
}

#endif // __PLAYER_UTILS_INCLUDE_FILE__
