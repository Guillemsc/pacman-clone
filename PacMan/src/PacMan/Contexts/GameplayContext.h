//
// Created by guillem on 6/30/25.
//

#ifndef GAMEPLAYCONTEXT_H
#define GAMEPLAYCONTEXT_H

#include "Context.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"

#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapPathfindingManager.h"
#include "PacMan/Gameplay/Pellets/Managers/PelletsLoadingManager.h"
#include "PacMan/Gameplay/Player/Managers/PlayerCollisionsManager.h"

namespace GEngine
{
	class Entity;
}

namespace PacMan
{
	class GhostsPrisionManager;
	class PlayerInputSystem;
	class GhostsLoadingManager;
	class PlayerLoaderManager;
	class MapMovementSystem;
	class MapPathfindingSystem;

	// Contains all the main gameplay setup and logic.
	class GameplayContext : public Context
	{
	public:
		explicit GameplayContext(GEngine::GEngineCoreModules* modules);

		tokoro::Async<void> OnLoadAsync() override;

	private:
		std::unique_ptr<MapMovementManager> _mapMovementManager;
		std::shared_ptr<MapMovementSystem> _mapMovementSystem;
		std::unique_ptr<MapPathfindingManager> _mapPathfindingManager;
		std::shared_ptr<MapPathfindingSystem> _mapPathfindingSystem;
		std::unique_ptr<GameplayEntities> _gameplayEntities;
		std::shared_ptr<PlayerLoaderManager> _playerLoaderManager;
		std::unique_ptr<PlayerCollisionsManager> _playerCollisionsManager;
		std::shared_ptr<GhostsLoadingManager> _ghostsLoaderManager;
		std::shared_ptr<GhostsPrisionManager> _ghostsPrisionManager;
		std::unique_ptr<PelletsLoadingManager> _pelletsLoadingManager;
		std::shared_ptr<PlayerInputSystem> _playerInputSystem;
	};
}

#endif //GAMEPLAYCONTEXT_H
