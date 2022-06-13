#include "BaseSystem.hpp"

#include <core/Application.hpp>
#include <core/Store.hpp>

#include <ecs/utils/BaseUtils.hpp>

namespace ECS
{
	void BaseSystem::onUpdate(float deltaTime, entt::registry& registry)
	{
		auto getGameDataStoreFn = []() {
			return Core::Application::getInstance().getStore()->getDataStore(Core::Store::Type::Game);
		};

		if (BaseUtils::isBaseCaptured(ChipComponent::Type::White)) {
			if (auto dataStore = getGameDataStoreFn()) {
				dataStore->setBool("lose", true);
			}
		}
		else if (BaseUtils::isBaseCaptured(ChipComponent::Type::Black)) {
			if (auto dataStore = getGameDataStoreFn()) {
				dataStore->setBool("win", true);
			}
		}
	}
}
