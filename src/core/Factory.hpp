#ifndef __FACTORY_INCLUDE_FILE__
#define __FACTORY_INCLUDE_FILE__

#include <functional>
#include <string>
#include <map>
#include <memory>

namespace Core
{
    class Factorable
    {
    public:
        Factorable() = default;
        virtual ~Factorable() = default;
    };

    class Factory final
    {
    public:
        using FactorablePtr = std::shared_ptr<Factorable>;
        using RegisterTypeCallback = std::function<FactorablePtr()>;

    public:
        Factory() = default;
        ~Factory() = default;

    public:
        template<typename T> void registerType(std::string_view id);
        FactorablePtr createType(std::string_view id) const;

    private:
        std::map<std::string, RegisterTypeCallback> _registerTypeCallbacks;
    };

    template<typename T>
    void Factory::registerType(std::string_view id)
    {
        _registerTypeCallbacks.emplace(std::string{id}, []() {
            return std::make_shared<T>();
        });
    }
}

#endif // __FACTORY_INCLUDE_FILE__
