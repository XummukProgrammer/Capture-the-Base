#ifndef __GAME_APPLICATION_DELEGATE_INCLUDE_FILE__
#define __GAME_APPLICATION_DELEGATE_INCLUDE_FILE__

#include <core/Application.hpp>

namespace Core
{
    class States;
}

namespace Game
{
    class GameApplicationDelegate final : public Core::ApplicationDelegate
    {
    public:
        GameApplicationDelegate() = default;
        ~GameApplicationDelegate() = default;

    public:
        void onInitStates(Core::States* statesPtr) override;
    };
}

#endif // __GAME_APPLICATION_DELEGATE_INCLUDE_FILE__
