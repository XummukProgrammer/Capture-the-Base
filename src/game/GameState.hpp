#ifndef __GAME_STATE_INCLUDE_FILE__
#define __GAME_STATE_INCLUDE_FILE__

#include <core/State.hpp>

namespace Core
{
    class DataStore;
}

namespace Game
{
    class GameState final : public Core::State
    {
    public:
        GameState() = default;
        ~GameState() = default;

    public:
        void onEnter() override;
        void onUpdate(float deltaTime) override;

    private:
        Core::DataStore* _gameDataStore = nullptr;
    };
}

#endif // __GAME_STATE_INCLUDE_FILE__
