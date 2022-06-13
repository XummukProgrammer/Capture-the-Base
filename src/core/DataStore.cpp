#include "DataStore.hpp"

namespace Core
{
    void DataStore::setBool(std::string_view id, bool value)
    {
        setVariable(id, Variable::Type::Bool, value);
    }

    bool DataStore::getBool(std::string_view id, bool defValue) const
    {
        if (auto valueOpt = getVariableValue<bool>(id, Variable::Type::Bool)) {
            return valueOpt.value();
        }
        return defValue;
    }

    void DataStore::setInt(std::string_view id, int value)
    {
        setVariable(id, Variable::Type::Int, value);
    }

    int DataStore::getInt(std::string_view id, int defValue) const
    {
        if (auto valueOpt = getVariableValue<int>(id, Variable::Type::Int)) {
            return valueOpt.value();
        }
        return defValue;
    }

    void DataStore::setFloat(std::string_view id, float value)
    {
        setVariable(id, Variable::Type::Float, value);
    }

    float DataStore::getFloat(std::string_view id, float defValue) const
    {
        if (auto valueOpt = getVariableValue<float>(id, Variable::Type::Float)) {
            return valueOpt.value();
        }
        return defValue;
    }

    void DataStore::setString(std::string_view id, const std::string& value)
    {
        setVariable(id, Variable::Type::String, value);
    }

    std::string DataStore::getString(std::string_view id, const std::string& defValue) const
    {
        if (auto valueOpt = getVariableValue<std::string>(id, Variable::Type::String)) {
            return valueOpt.value();
        }
        return defValue;
    }

    bool DataStore::has(std::string_view id) const
    {
        return getVariable(id) != nullptr;
    }

    DataStore::VariablePtr DataStore::makeVariable(Variable::Type type, std::any value)
    {
        auto variablePtr = std::make_unique<Variable>();
        variablePtr->type = type;
        variablePtr->value = value;
        return variablePtr;
    }

    void DataStore::setVariable(std::string_view id, Variable::Type type, std::any value)
    {
        if (auto variablePtr = getVariable(id)) {
            variablePtr->type = type;
            variablePtr->value = value;
        }
        else {
            addVariable(id, makeVariable(type, value));
        }
    }

    void DataStore::addVariable(std::string_view id, VariablePtr&& variablePtr)
    {
        _variables.emplace(std::string{ id }, std::move(variablePtr));
    }

    DataStore::VariablePtr::pointer DataStore::getVariable(std::string_view id) const
    {
        auto it = _variables.find(std::string{id});
        if (it != _variables.end()) {
            return it->second.get();
        }
        return nullptr;
    }
}
