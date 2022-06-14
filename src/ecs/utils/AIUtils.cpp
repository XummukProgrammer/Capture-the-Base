#include "AIUtils.hpp"

#include <core/Application.hpp>

#include <ecs/ECSWorld.hpp>

#include <ecs/components/AIComponent.hpp>
#include <ecs/components/ChipComponent.hpp>
#include <ecs/components/CellComponent.hpp>

#include <ecs/utils/ChipsUtils.hpp>
#include <ecs/utils/BaseUtils.hpp>
#include <ecs/utils/CellsUtils.hpp>

namespace ECS
{
    void AIUtils::setAI(entt::entity entity)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        registry.emplace_or_replace<AIComponent>(entity);
    }

    void AIUtils::unsetAI(entt::entity entity)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        registry.remove<AIComponent>(entity);
    }

    void AIUtils::generatePath(entt::entity entity)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        auto chipComponent = registry.try_get<ChipComponent>(entity);
        auto aiComponent = registry.try_get<AIComponent>(entity);
        if (!chipComponent || !aiComponent) {
            return;
        }

        const auto& chipIndexes = chipComponent->indexes;
        auto enemyChipType = ChipsUtils::reverseType(chipComponent->type);
        const auto& chipBaseEntities = BaseUtils::getBaseEntities(enemyChipType);

        // TODO: Choice normal entity
        auto chipBaseEntity = chipBaseEntities[0];
        auto baseCellComponent = registry.try_get<CellComponent>(chipBaseEntity);
        const auto& chipBaseEndexes = baseCellComponent->indexes;

        std::vector<sf::Vector2i> path;

        sf::Vector2i point = chipIndexes;

        do
        {
            // Base on top
            if (point.y < chipBaseEndexes.y) {
                ++point.y;
            }
            // Base on down
            else if (point.y > chipBaseEndexes.y) {
                --point.y;
            }
            path.push_back(point);

            // base on right
            if (point.x < chipBaseEndexes.x) {
                ++point.x;
            }
            // Base on left
            else if (point.x > chipBaseEndexes.x) {
                --point.x;
            }
            path.push_back(point);
        }
        while (point != chipBaseEndexes);

        for (const auto& indexes : path) {
            //CellsUtils::setMoveableCell(CellsUtils::getCellFromIndexes(indexes));
            aiComponent->pathQueue.push(indexes);
        }
    }

    void AIUtils::moveFromPath(entt::entity entity)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        auto aiComponent = registry.try_get<AIComponent>(entity);
        if (!aiComponent) {
            return;
        }

        if (aiComponent->pathQueue.empty()) {
            generatePath(entity);
        }

        const auto& pathIndexes = aiComponent->pathQueue.front();
        aiComponent->pathQueue.pop();

        ChipsUtils::moveChip(entity, pathIndexes);
    }
}
