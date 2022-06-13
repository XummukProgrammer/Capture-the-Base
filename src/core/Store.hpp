#ifndef __STORE_INCLUDE_FILE__
#define __STORE_INCLUDE_FILE__

#include "DataStore.hpp"

#include <map>
#include <memory>

namespace Core
{
	class Store final
	{
	public:
		enum class Type
		{
			Game
		};

	public:
		using DataStorePtr = std::unique_ptr<DataStore>;

	public:
		Store() = default;
		~Store() = default;

	public:
		void create();

	public:
		DataStorePtr::pointer getDataStore(Type type) const;

	private:
		std::map<Type, DataStorePtr> _dataStores;
	};
}

#endif // __STORE_INCLUDE_FILE__
