#include "PlayerUtils.hpp"

#include <core/Application.hpp>
#include <core/Window.hpp>
#include <core/Store.hpp>

#include <ecs/ECSWorld.hpp>

#include <ecs/components/ChipComponent.hpp>
#include <ecs/components/VisualObjectComponent.hpp>
#include <ecs/components/ChipTargetComponent.hpp>
#include <ecs/components/CellComponent.hpp>

#include <ecs/utils/CellsUtils.hpp>
#include <ecs/utils/ChipsUtils.hpp>

namespace ECS
{
    void PlayerUtils::trySetTargetChip()
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        auto view = registry.view<ChipComponent, VisualObjectComponent>();
        view.each([&registry](entt::entity entity, const ChipComponent& chipComponent, const VisualObjectComponent& visualObjectComponent) {
            if (chipComponent.type == ChipComponent::Type::White) {
                if (PlayerUtils::isContainsWithMousePosition(visualObjectComponent)) {
                    ChipsUtils::unsetTargetChip();
                    CellsUtils::unsetMoveableCells();

                    ChipsUtils::setTargetChip(entity);

                    auto&& moveableCells = CellsUtils::getMoveableCellsFromIndexes(chipComponent.indexes);
                    for (const auto moveableCell : moveableCells) {
                        CellsUtils::setMoveableCell(moveableCell);
                    }
                }
            }
        });
    }

    void PlayerUtils::tryMoveTargetChip()
    {
        auto& registry = Core::Application::getInstance().getECSWorld()->getRegistry();

        auto view = registry.view<CellMoveableComponent, CellComponent, VisualObjectComponent>();
        view.each([](entt::entity entity, const CellMoveableComponent&, const CellComponent& cellComponent, VisualObjectComponent& visualObjectComponent) {
            if (PlayerUtils::isContainsWithMousePosition(visualObjectComponent)) {
                ChipsUtils::moveChip(ChipsUtils::getTargetChip(), cellComponent.indexes);

                ChipsUtils::unsetTargetChip();
                CellsUtils::unsetMoveableCells();

                if (auto dataStore = Core::Application::getInstance().getStore()->getDataStore(Core::Store::Type::Game)) {
                    dataStore->setBool("chipMoves", true);
                }
            }
        });
    }

    sf::Vector2f PlayerUtils::getMousePosition()
    {
        auto&& mousePosition = Core::Application::getInstance().getWindow()->getMousePosition();
        sf::Vector2f flMousePosition = { static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) };
        return flMousePosition;
    }

    bool PlayerUtils::isContainsWithMousePosition(const VisualObjectComponent& visualObjectComponent)
    {
        auto& sprite = visualObjectComponent.visualObjectPtr->getSprite();
        return sprite.getGlobalBounds().contains(PlayerUtils::getMousePosition());
    }
}
