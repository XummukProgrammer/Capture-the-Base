#include "Store.hpp"

namespace Core
{
	void Store::create()
	{
		_dataStores[Type::Game] = std::make_unique<DataStore>();
	}

	Store::DataStorePtr::pointer Store::getDataStore(Type type) const
	{
		auto it = _dataStores.find(type);
		if (it != _dataStores.end()) {
			return it->second.get();
		}
		return nullptr;
	}
}
