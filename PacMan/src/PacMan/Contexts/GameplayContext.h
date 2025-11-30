//
// Created by guillem on 6/30/25.
//

#ifndef GAMEPLAYCONTEXT_H
#define GAMEPLAYCONTEXT_H

#include "Context.h"



namespace GEngine
{
	class Entity;
}

namespace PacMan
{
	class GhostsPrisionManager;
	class MapPathfindingManager;
	class PlayerInputSystem;
	class GhostsLoaderManager;
	class PlayerLoaderManager;
	class GameplayEntities;
	class MapMovementSystem;
	class MapMovementManager;
	class MapPathfindingSystem;

	class GameplayContext : public Context
	{
	public:
		explicit GameplayContext(GEngine::GEngineCoreModules* modules);

		tokoro::Async<void> OnLoadAsync() override;

	private:
		std::shared_ptr<MapMovementManager> _mapMovementManager;
		std::shared_ptr<MapMovementSystem> _mapMovementSystem;
		std::shared_ptr<MapPathfindingManager> _mapPathfindingManager;
		std::shared_ptr<MapPathfindingSystem> _mapPathfindingSystem;
		std::shared_ptr<GameplayEntities> _gameplayEntities;
		std::shared_ptr<PlayerLoaderManager> _playerLoaderManager;
		std::shared_ptr<GhostsLoaderManager> _ghostsLoaderManager;
		std::shared_ptr<GhostsPrisionManager> _ghostsPrisionManager;
		std::shared_ptr<PlayerInputSystem> _playerInputSystem;
	};
}

#endif //GAMEPLAYCONTEXT_H
