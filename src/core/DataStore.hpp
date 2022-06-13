#ifndef __DATA_STORE_INCLUDE_FILE__
#define __DATA_STORE_INCLUDE_FILE__

#include <string>
#include <map>
#include <memory>
#include <any>
#include <optional>

namespace Core
{
	class DataStore final
	{
	public:
		struct Variable
		{
			enum class Type
			{
				Bool,
				Int,
				Float,
				String
			};
			Type type;
			std::any value;
		};

	public:
		using VariablePtr = std::unique_ptr<Variable>;

	public:
		DataStore() = default;
		~DataStore() = default;
		
	public:
		void setBool(std::string_view id, bool value);
		bool getBool(std::string_view id, bool defValue = false) const;

		void setInt(std::string_view id, int value);
		int getInt(std::string_view id, int defValue = 0) const;

		void setFloat(std::string_view id, float value);
		float getFloat(std::string_view id, float defValue = 0.f) const;

		void setString(std::string_view id, const std::string& value);
		std::string getString(std::string_view id, const std::string& defValue = "") const;

		bool has(std::string_view id) const;

	private:
		VariablePtr makeVariable(Variable::Type type, std::any value);
		void setVariable(std::string_view id, Variable::Type type, std::any value);
		void addVariable(std::string_view id, VariablePtr&& variablePtr);
		VariablePtr::pointer getVariable(std::string_view id) const;

		template<typename T> std::optional<T> getVariableValue(std::string_view id, Variable::Type type) const;

	private:
		std::map<std::string, VariablePtr> _variables;
	};
	
	template<typename T>
	std::optional<T> DataStore::getVariableValue(std::string_view id, Variable::Type type) const
	{
		if (auto variablePtr = getVariable(id)) {
			if (variablePtr->type == type) {
				return std::any_cast<T>(variablePtr->value);
			}
		}
		return {};
	}
}

#endif // __DATA_STORE_INCLUDE_FILE__
