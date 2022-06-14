#include "AISystem.hpp"

#include <core/Application.hpp>
#include <core/Store.hpp>

#include <ecs/utils/ChipsUtils.hpp>
#include <ecs/utils/CellsUtils.hpp>
#include <ecs/utils/AIUtils.hpp>

namespace ECS
{
    void AISystem::onUpdate(float deltaTime, entt::registry& registry)
    {
        if (auto dataStore = Core::Application::getInstance().getStore()->getDataStore(Core::Store::Type::Game)) {
            if (dataStore->getBool("playerControl") || dataStore->getBool("chipMoves")) {
                return;
            }
        }

        // TODO: Choice normal chip
        AIUtils::moveFromPath(ChipsUtils::getChipFromIndexes({ 2, 2 }));


        if (auto dataStore = Core::Application::getInstance().getStore()->getDataStore(Core::Store::Type::Game)) {
            dataStore->setBool("chipMoves", true);
        }
    }
}
