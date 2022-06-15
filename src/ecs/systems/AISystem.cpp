#include "AISystem.hpp"

#include <core/Application.hpp>
#include <core/Store.hpp>

#include <ecs/utils/ChipsUtils.hpp>
#include <ecs/utils/CellsUtils.hpp>
#include <ecs/utils/AIUtils.hpp>

#include <random>

namespace ECS
{
    void AISystem::onUpdate(float deltaTime, entt::registry& registry)
    {
        if (auto dataStore = Core::Application::getInstance().getStore()->getDataStore(Core::Store::Type::Game)) {
            if (dataStore->getBool("playerControl") || dataStore->getBool("chipMoves")) {
                return;
            }
        }

        const auto& moveableEntities = AIUtils::getMoveableEntities();
        if (!moveableEntities.empty()) {
            std::random_device random_device;
            std::mt19937 generator(random_device());

            std::uniform_int_distribution<> distribution(0, static_cast<int>(moveableEntities.size()) - 1);
            const int randomIndex = distribution(generator);

            AIUtils::moveFromPath(moveableEntities[randomIndex]);
        }
        

        if (auto dataStore = Core::Application::getInstance().getStore()->getDataStore(Core::Store::Type::Game)) {
            dataStore->setBool("chipMoves", true);
        }
    }
}
