//
// Created by guillem on 12/5/25.
//

#ifndef PLAYERDEATHMANAGER_H
#define PLAYERDEATHMANAGER_H

#include "tokoro.h"

namespace PacMan
{
	class GhostsLoadingManager;
}

namespace GEngine
{
	class CoroutinesRunner;
}

namespace PacMan
{
	class GhostsPrisionManager;
	class EntitiesManager;
	class PlayerLoaderManager;

	class PlayerDeathManager
	{
	public:
		PlayerDeathManager(
			GEngine::CoroutinesRunner* coroutines,
			EntitiesManager* entitiesManager,
			GhostsPrisionManager* ghostsPrisionManager,
			PlayerLoaderManager* playerLoaderManager,
			GhostsLoadingManager* ghostsLoadingManager
			);

		void RunDeath();

	private:
		[[nodiscard]] tokoro::Async<void> RunDeathSequenceAsync() const;

	private:
		GEngine::CoroutinesRunner* const _coroutines;
		EntitiesManager* const _entitiesManager;
		GhostsPrisionManager* const _ghostsPrisionManager;
		PlayerLoaderManager* const _playerLoaderManager;
		GhostsLoadingManager* const _ghostsLoadingManager;
	};
}

#endif //PLAYERDEATHMANAGER_H
