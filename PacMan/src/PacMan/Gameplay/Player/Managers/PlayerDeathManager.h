//
// Created by guillem on 12/5/25.
//

#ifndef PLAYERDEATHMANAGER_H
#define PLAYERDEATHMANAGER_H

#include "tokoro.h"

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
			PlayerLoaderManager* playerLoaderManager
			);

		void RunDeath();

	private:
		tokoro::Async<void> RunDeathSequenceAsync();

	private:
		GEngine::CoroutinesRunner* const _coroutines;
		EntitiesManager* const _entitiesManager;
		GhostsPrisionManager* const _ghostsPrisionManager;
		PlayerLoaderManager* const _playerLoaderManager;
	};
}

#endif //PLAYERDEATHMANAGER_H
