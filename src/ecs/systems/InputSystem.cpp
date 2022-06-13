#include "InputSystem.hpp"

#include <core/Application.hpp>
#include <core/Window.hpp>

#include <ecs/components/ChipComponent.hpp>
#include <ecs/components/VisualObjectComponent.hpp>
#include <ecs/components/ChipTargetComponent.hpp>
#include <ecs/components/CellComponent.hpp>

#include <ecs/utils/CellsUtils.hpp>
#include <ecs/utils/ChipsUtils.hpp>

#include <SFML/Graphics.hpp>

namespace ECS
{
    void InputSystem::onUpdate(float deltaTime, entt::registry& registry)
    {
        if (_mouseClickTimerDelay > 0.f) {
            _mouseClickTimerDelay -= deltaTime;
            return;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            auto&& mousePosition = Core::Application::getInstance().getWindow()->getMousePosition();
            sf::Vector2f flMousePosition = { static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) };
            
            {
                auto view = registry.view<ChipComponent, VisualObjectComponent>();
                view.each([this, &registry, flMousePosition](entt::entity entity, const ChipComponent& chipComponent, const VisualObjectComponent& visualObjectComponent) {
                    if (chipComponent.type == ChipComponent::Type::White) {
                        auto& sprite = visualObjectComponent.visualObjectPtr->getSprite();
                        if (sprite.getGlobalBounds().contains(flMousePosition)) {
                            ChipsUtils::unsetTargetChip();
                            CellsUtils::unsetMoveableCells();

                            ChipsUtils::setTargetChip(entity);

                            auto&& moveableCells = CellsUtils::getMoveableCellsFromIndexes(chipComponent.indexes);
                            for (const auto moveableCell : moveableCells) {
                                CellsUtils::setMoveableCell(moveableCell);
                            }

                            _mouseClickTimerDelay = 0.1f;
                        }
                    }
                    });
            }
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            auto&& mousePosition = Core::Application::getInstance().getWindow()->getMousePosition();
            sf::Vector2f flMousePosition = { static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y) };

            {
                auto view = registry.view<CellMoveableComponent, CellComponent, VisualObjectComponent>();
                view.each([this, flMousePosition](entt::entity entity, const CellMoveableComponent&, const CellComponent& cellComponent,
                    VisualObjectComponent& visualObjectComponent) {
                        auto& sprite = visualObjectComponent.visualObjectPtr->getSprite();
                        if (sprite.getGlobalBounds().contains(flMousePosition)) {
                            ChipsUtils::moveChip(ChipsUtils::getTargetChip(), cellComponent.indexes);

                            ChipsUtils::unsetTargetChip();
                            CellsUtils::unsetMoveableCells();

                            _mouseClickTimerDelay = 0.1f;
                        }
                    });
            }
        }
    }
}
