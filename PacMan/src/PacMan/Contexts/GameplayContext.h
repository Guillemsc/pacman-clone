//
// Created by guillem on 6/30/25.
//

#ifndef GAMEPLAYCONTEXT_H
#define GAMEPLAYCONTEXT_H

#include "Context.h"
#include "PacMan/Gameplay/Cameras/Managers/CameraManager.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"

#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapPathfindingManager.h"
#include "PacMan/Gameplay/Pellets/Managers/PelletsLoadingManager.h"
#include "PacMan/Gameplay/Player/Managers/PlayerCollisionsManager.h"
#include "PacMan/Gameplay/Player/Managers/PlayerDeathManager.h"
#include "PacMan/Gameplay/Entities/Managers/EntitiesManager.h"
#include "PacMan/Gameplay/Ghosts/Managers/GhostsLoadingManager.h"
#include "PacMan/Gameplay/MapLoading/Managers/MapLoadingManager.h"
#include "PacMan/Gameplay/Player/Managers/PlayerLoaderManager.h"

namespace GEngine
{
	class Entity;
}

namespace PacMan
{
	class PlayerInputSystem;

	// Contains all the main gameplay setup and logic.
	class GameplayContext : public Context
	{
	public:
		explicit GameplayContext(GEngine::GEngineCoreModules* modules);

		tokoro::Async<void> OnLoadAsync() override;
		void OnDispose() override;

	private:
		std::shared_ptr<CameraManager> _cameraManager;
		std::unique_ptr<MapLoadingManager> _mapLoadingManager;
		std::unique_ptr<MapMovementManager> _mapMovementManager;
		std::unique_ptr<MapPathfindingManager> _mapPathfindingManager;
		std::unique_ptr<GameplayEntities> _gameplayEntities;
		std::unique_ptr<EntitiesManager> _entitiesManager;
		std::unique_ptr<PlayerLoaderManager> _playerLoaderManager;
		std::unique_ptr<PlayerCollisionsManager> _playerCollisionsManager;
		std::unique_ptr<PlayerDeathManager> _playerDeathManager;
		std::shared_ptr<GhostsLoadingManager> _ghostsLoaderManager;
		std::shared_ptr<GhostsPrisionManager> _ghostsPrisionManager;
		std::unique_ptr<PelletsLoadingManager> _pelletsLoadingManager;
		std::shared_ptr<PlayerInputSystem> _playerInputSystem;
	};
}

#endif //GAMEPLAYCONTEXT_H
