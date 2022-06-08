#ifndef __STATES_INCLUDE_FILE__
#define __STATES_INCLUDE_FILE__

#include "State.hpp"

#include <map>
#include <string>
#include <memory>

namespace Core
{
    class States final
    {
    public:
        using StatePtr = std::unique_ptr<State>;

    public:
        States() = default;
        ~States() = default;

    public:
        void addState(std::string_view id, StatePtr&& state);

        void setCurrentState(std::string_view id);

    public:
        void onUpdate(float deltaTime);

    private:
        State* getCurrentState() const;

    private:
        std::map<std::string, StatePtr> _states;
        std::string _currentState; // Use iterator?
    };
}

#endif // __STATES_INCLUDE_FILE__
