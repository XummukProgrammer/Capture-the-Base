
set(GAME_HEADERS
	src/core/Application.hpp
	src/core/Asset.hpp
	src/core/Assets.hpp
	src/core/Factory.hpp
	src/core/VisualObjects.hpp
	src/core/State.hpp
	src/core/States.hpp
	src/core/VisualObject.hpp
	src/core/Window.hpp
	
	src/ecs/ECSWorld.hpp
	
	src/ecs/components/TransformComponent.hpp
	src/ecs/components/VisualObjectComponent.hpp
	src/ecs/components/TextureComponent.hpp
	src/ecs/components/CellComponent.hpp
	src/ecs/components/ChipComponent.hpp
	src/ecs/components/ChipTargetComponent.hpp
	src/ecs/components/TeamComponent.hpp
	src/ecs/components/TextComponent.hpp
	src/ecs/components/InputEventComponent.hpp
	
	src/ecs/systems/System.hpp
	src/ecs/systems/Systems.hpp
	src/ecs/systems/UpdateVisualObjectsSystem.hpp
	src/ecs/systems/UpdateTextsSystem.hpp
	src/ecs/systems/InputSystem.hpp
	src/ecs/systems/BaseSystem.hpp
	
	src/ecs/utils/VisualObjectsUtils.hpp
	src/ecs/utils/CellsUtils.hpp
	src/ecs/utils/ChipsUtils.hpp
	src/ecs/utils/TeamsUtils.hpp
	src/ecs/utils/TextsUtils.hpp
	src/ecs/utils/PlayerUtils.hpp
	src/ecs/utils/BaseUtils.hpp
	
	src/game/GameApplicationDelegate.hpp
	src/game/GameState.hpp
)

set(GAME_SOURCES
	src/main.cpp
	
	src/core/Application.cpp
	src/core/Asset.cpp
	src/core/Assets.cpp
	src/core/Factory.cpp
	src/core/VisualObjects.cpp
	src/core/State.cpp
	src/core/States.cpp
	src/core/VisualObject.cpp
	src/core/Window.cpp
	
	src/ecs/ECSWorld.cpp
	
	src/ecs/systems/System.cpp
	src/ecs/systems/Systems.cpp
	src/ecs/systems/UpdateVisualObjectsSystem.cpp
	src/ecs/systems/UpdateTextsSystem.cpp
	src/ecs/systems/InputSystem.cpp
	src/ecs/systems/BaseSystem.cpp
	
	src/ecs/utils/VisualObjectsUtils.cpp
	src/ecs/utils/CellsUtils.cpp
	src/ecs/utils/ChipsUtils.cpp
	src/ecs/utils/TeamsUtils.cpp
	src/ecs/utils/TextsUtils.cpp
	src/ecs/utils/PlayerUtils.cpp
	src/ecs/utils/BaseUtils.cpp
	
	src/game/GameApplicationDelegate.cpp
	src/game/GameState.cpp
)
