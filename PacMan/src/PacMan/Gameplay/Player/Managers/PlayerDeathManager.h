//
// Created by guillem on 12/5/25.
//

#ifndef PLAYERDEATHMANAGER_H
#define PLAYERDEATHMANAGER_H

#include "tokoro.h"

namespace PacMan
{
	class GhostsBehaviourManager;
}

namespace GEngine
{
	class CancellationToken;
	class CancellationTokenSource;
	class CoroutinesRunner;
}

namespace PacMan
{
	class GhostsPrisionManager;
	class EntitiesManager;
	class PlayerLoaderManager;
	class GhostsLoadingManager;

	class PlayerDeathManager
	{
	public:
		PlayerDeathManager(
			GEngine::CoroutinesRunner* coroutines,
			EntitiesManager* entitiesManager,
			GhostsPrisionManager* ghostsPrisionManager,
			PlayerLoaderManager* playerLoaderManager,
			GhostsLoadingManager* ghostsLoadingManager,
			GhostsBehaviourManager* ghostsBehaviourManager
			);

		void RunDeath();

	private:
		[[nodiscard]] tokoro::Async<void> RunDeathSequenceAsync(GEngine::CancellationToken cancellationToken) const;

	private:
		GEngine::CoroutinesRunner* const _coroutines;
		EntitiesManager* const _entitiesManager;
		GhostsPrisionManager* const _ghostsPrisionManager;
		PlayerLoaderManager* const _playerLoaderManager;
		GhostsLoadingManager* const _ghostsLoadingManager;
		GhostsBehaviourManager* const _ghostsBehaviourManager;

		std::shared_ptr<GEngine::CancellationTokenSource> _cancellationTokenSource;
	};
}

#endif //PLAYERDEATHMANAGER_H
