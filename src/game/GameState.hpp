#ifndef __GAME_STATE_INCLUDE_FILE__
#define __GAME_STATE_INCLUDE_FILE__

#include <core/State.hpp>

namespace Game
{
    class GameState final : public Core::State
    {
    public:
        GameState() = default;
        ~GameState() = default;

    public:
        void onUpdate(float deltaTime) override;
    };
}

#endif // __GAME_STATE_INCLUDE_FILE__
