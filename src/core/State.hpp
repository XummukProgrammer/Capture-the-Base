#ifndef __STATE_INCLUDE_FILE__
#define __STATE_INCLUDE_FILE__

namespace Core
{
    class State
    {
    public:
        State() = default;
        virtual ~State() = default;

    public:
        virtual void onEnter() {}
        virtual void onExit() {}

        virtual void onUpdate(float deltaTime) {}
    };
}

#endif // __STATE_INCLUDE_FILE__
