cmake_minimum_required(VERSION 3.31)
project(PacMan)

set(CMAKE_CXX_STANDARD 20)

add_executable(PacMan src/PacMan/Bootstrap/main.cpp
        src/PacMan/Games/PacManGame.h
        src/PacMan/Games/PacManGame.cpp
        src/PacMan/Flow/FlowManager.cpp
        src/PacMan/Flow/FlowManager.h
        src/PacMan/Contexts/GameplayContext.cpp
        src/PacMan/Contexts/GameplayContext.h
        src/PacMan/Contexts/Context.cpp
        src/PacMan/Contexts/Context.h
        src/PacMan/Contexts/ContextsStack.cpp
        src/PacMan/Contexts/ContextsStack.h
        src/PacMan/Gameplay/Input/Systems/PlayerInputSystem.cpp
        src/PacMan/Gameplay/Input/Systems/PlayerInputSystem.h
        src/PacMan/Contexts/MetaContext.cpp
        src/PacMan/Contexts/MetaContext.h
        src/PacMan/Gameplay/Entities/Data/GameplayEntities.h
        src/PacMan/Contexts/SharedContext.cpp
        src/PacMan/Contexts/SharedContext.h
        src/PacMan/Gameplay/MapMovement/Managers/MapMovementManager.cpp
        src/PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h
        src/PacMan/Gameplay/MapLoading/Data/LoadedMapData.h
        src/PacMan/Gameplay/MapLoading/Managers/MapLoadingManager.cpp
        src/PacMan/Gameplay/MapLoading/Managers/MapLoadingManager.h
        src/PacMan/Gameplay/Player/Managers/PlayerLoaderManager.cpp
        src/PacMan/Gameplay/Player/Managers/PlayerLoaderManager.h
        src/PacMan/Gameplay/Ghosts/Managers/GhostsLoadingManager.cpp
        src/PacMan/Gameplay/Ghosts/Managers/GhostsLoadingManager.h
        src/PacMan/Gameplay/Ghosts/Enums/GhostType.h
        src/PacMan/Gameplay/MapMovement/Managers/MapPathfindingManager.cpp
        src/PacMan/Gameplay/MapMovement/Managers/MapPathfindingManager.h
        src/PacMan/Gameplay/MapMovement/Data/PathfindingNode.h
        src/PacMan/Gameplay/MapMovement/Comparers/PathfindingComparer.h
        src/PacMan/Gameplay/MapMovement/Components/MapMovementComponent.cpp
        src/PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h
        src/PacMan/Gameplay/Ghosts/Components/GhostAiComponent.cpp
        src/PacMan/Gameplay/Ghosts/Components/GhostAiComponent.h
        src/PacMan/Gameplay/Ghosts/Components/RedGhostAiComponent.cpp
        src/PacMan/Gameplay/Ghosts/Components/RedGhostAiComponent.h
        src/PacMan/Gameplay/Ghosts/Managers/GhostsPrisionManager.cpp
        src/PacMan/Gameplay/Ghosts/Managers/GhostsPrisionManager.h
        src/PacMan/Gameplay/Ghosts/Data/GhostPrisionSlotData.h
        src/PacMan/Gameplay/Ghosts/Data/LoadedGhostsData.h
        src/PacMan/Gameplay/Collisions/Enums/CollisionLayers.h
        src/PacMan/Gameplay/Entities/Components/EntityIdComponent.cpp
        src/PacMan/Gameplay/Entities/Components/EntityIdComponent.h
        src/PacMan/Gameplay/Entities/Enums/EntityType.h
        src/PacMan/Gameplay/Player/Components/PlayerAnimationComponent.cpp
        src/PacMan/Gameplay/Player/Components/PlayerAnimationComponent.h
        src/PacMan/Gameplay/Pellets/Managers/PelletsLoadingManager.cpp
        src/PacMan/Gameplay/Pellets/Managers/PelletsLoadingManager.h
        src/PacMan/Gameplay/Player/Managers/PlayerCollisionsManager.cpp
        src/PacMan/Gameplay/Player/Managers/PlayerCollisionsManager.h
        src/PacMan/Gameplay/Player/Managers/PlayerDeathManager.cpp
        src/PacMan/Gameplay/Player/Managers/PlayerDeathManager.h
        src/PacMan/Gameplay/Entities/Managers/EntitiesManager.cpp
        src/PacMan/Gameplay/Entities/Managers/EntitiesManager.h
        src/PacMan/Gameplay/Cameras/Managers/CameraManager.cpp
        src/PacMan/Gameplay/Cameras/Managers/CameraManager.h
        src/PacMan/Shared/Camera/Data/CameraData.h
        src/PacMan/Gameplay/Ghosts/Components/CianGhostAiComponent.cpp
        src/PacMan/Gameplay/Ghosts/Components/CianGhostAiComponent.h
        src/PacMan/Gameplay/Ghosts/Components/PinkGhostAiComponent.cpp
        src/PacMan/Gameplay/Ghosts/Components/PinkGhostAiComponent.h
        src/PacMan/Gameplay/Ghosts/Components/OrangeGhostAiComponent.cpp
        src/PacMan/Gameplay/Ghosts/Components/OrangeGhostAiComponent.h
)

target_link_libraries(PacMan PRIVATE GEngineCore)

target_include_directories(PacMan PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
