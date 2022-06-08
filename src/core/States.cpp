#include "States.hpp"

namespace Core
{
    void States::addState(std::string_view id, StatePtr&& state)
    {
        _states.emplace(std::string{id}, std::move(state));
    }

    void States::setCurrentState(std::string_view id)
    {
        if (auto prevState = getCurrentState()) {
            prevState->onExit();
        }

        _currentState = id;

        if (auto currState = getCurrentState()) {
            currState->onEnter();
        }
    }

    void States::onUpdate(float deltaTime)
    {
        if (auto state = getCurrentState()) {
            state->onUpdate(deltaTime);
        }
    }

    State* States::getCurrentState() const
    {
        if (!_currentState.empty()) {
            auto it = _states.find(_currentState);
            if (it != _states.end()) {
                return it->second.get();
            }
        }
        return nullptr;
    }
}
