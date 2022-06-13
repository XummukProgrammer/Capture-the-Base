#include "BaseSystem.hpp"

#include <ecs/utils/BaseUtils.hpp>

namespace ECS
{
	void BaseSystem::onUpdate(float deltaTime, entt::registry& registry)
	{
		if (BaseUtils::isBaseCaptured(ChipComponent::Type::White)) {
			// Lose
			auto i = 0;
		}
		else if (BaseUtils::isBaseCaptured(ChipComponent::Type::Black)) {
			// Win
			auto i = 0;
		}
	}
}
