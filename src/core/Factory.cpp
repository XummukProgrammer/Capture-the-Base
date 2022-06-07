#include "Factory.hpp"

namespace Core
{
    Factory::FactorablePtr Factory::createType(std::string_view id) const
    {
        auto it = _registerTypeCallbacks.find(std::string{id});
        if (it != _registerTypeCallbacks.end()) {
            return it->second();
        }
        return nullptr;
    }
}
