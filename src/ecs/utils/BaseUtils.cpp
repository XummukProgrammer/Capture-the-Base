#include "BaseUtils.hpp"

#include <core/Application.hpp>

#include <ecs/ECSWorld.hpp>
#include <ecs/components/CellComponent.hpp>

#include <ecs/utils/ChipsUtils.hpp>

namespace ECS
{
    void BaseUtils::setBase(entt::entity entity, ChipComponent::Type type)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        auto& chipBaseComponent = registry.emplace_or_replace<ChipBaseComponent>(entity);
        chipBaseComponent.type = type;
    }

    void BaseUtils::unsetBase(entt::entity entity)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        if (!registry.valid(entity)) {
            return;
        }

        registry.remove<ChipBaseComponent>(entity);
    }

    bool BaseUtils::isBaseCaptured(ChipComponent::Type type)
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();
        auto view = registry.view<CellComponent, ChipBaseComponent>();
        
        for (auto entity : view) {
            const auto& chipBaseComponent = registry.get<ChipBaseComponent>(entity);

            if (chipBaseComponent.type == type) {
                const auto& cellComponent = registry.get<CellComponent>(entity);
                auto chipEntity = ChipsUtils::getChipFromIndexes(cellComponent.indexes);
                if (!registry.valid(chipEntity)) {
                    return false;
                }

                auto& chipComponent = registry.get<ChipComponent>(chipEntity);
                if (chipComponent.type == type) {
                    return false;
                }
            }
        }

        return true;
    }
}
