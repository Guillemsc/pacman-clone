//
// Created by guillem on 11/26/25.
//

#ifndef PLAYERLOADERMANAGER_H
#define PLAYERLOADERMANAGER_H
#include <memory>

#include "glm/fwd.hpp"

namespace GEngine
{
	class Scene;
	class GEngineCoreModules;
}

namespace PacMan
{
	class PlayerInputSystem;
	class GameplayEntities;
	class MapMovementManager;

	class PlayerLoaderManager
	{
	public:
		explicit PlayerLoaderManager(
			GEngine::GEngineCoreModules* modules,
			GEngine::Scene* scene,
			MapMovementManager* mapMovementManager,
			PlayerInputSystem* playerInputSystem,
			GameplayEntities* gameplayEntities
			);

		void LoadPlayer(const glm::i32vec2& gridPosition) const;

	private:
		GEngine::GEngineCoreModules* const _modules;
		GEngine::Scene* const _scene;
		MapMovementManager* const _mapMovementManager;
		PlayerInputSystem* const _playerInputSystem;
		GameplayEntities* const _gameplayEntities;
	};
}

#endif //PLAYERLOADERMANAGER_H
