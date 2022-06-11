
set(GAME_HEADERS
	src/core/Application.hpp
	src/core/Asset.hpp
	src/core/Assets.hpp
	src/core/Factory.hpp
	src/core/RenderVisualObjects.hpp
	src/core/State.hpp
	src/core/States.hpp
	src/core/VisualObject.hpp
	src/core/Window.hpp
	
	src/ecs/ECSWorld.hpp
	src/ecs/components/TransformComponent.hpp
	src/ecs/components/VisualObjectComponent.hpp
	src/ecs/components/CellComponent.hpp
	src/ecs/components/ChipComponent.hpp
	src/ecs/systems/System.hpp
	src/ecs/systems/Systems.hpp
	src/ecs/systems/UpdateVisualObjectsSystem.hpp
	src/ecs/utils/RenderVisualObjectsECSUtils.hpp
	src/ecs/utils/CellsECSUtils.hpp
	src/ecs/utils/ChipsECSUtils.hpp
	
	src/game/GameApplicationDelegate.hpp
	src/game/GameState.hpp
)

set(GAME_SOURCES
	src/main.cpp
	
	src/core/Application.cpp
	src/core/Asset.cpp
	src/core/Assets.cpp
	src/core/Factory.cpp
	src/core/RenderVisualObjects.cpp
	src/core/State.cpp
	src/core/States.cpp
	src/core/VisualObject.cpp
	src/core/Window.cpp
	
	src/ecs/ECSWorld.cpp
	src/ecs/components/TransformComponent.cpp
	src/ecs/components/VisualObjectComponent.cpp
	src/ecs/components/CellComponent.cpp
	src/ecs/components/ChipComponent.cpp
	src/ecs/systems/System.cpp
	src/ecs/systems/Systems.cpp
	src/ecs/systems/UpdateVisualObjectsSystem.cpp
	src/ecs/utils/RenderVisualObjectsECSUtils.cpp
	src/ecs/utils/CellsECSUtils.cpp
	src/ecs/utils/ChipsECSUtils.cpp
	
	src/game/GameApplicationDelegate.cpp
	src/game/GameState.cpp
)
