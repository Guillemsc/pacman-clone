//
// Created by guillem on 12/5/25.
//

#include "PlayerDeathManager.h"

#include "PlayerLoaderManager.h"
#include "GEngine/Coroutines/CoroutinesRunner.h"
#include "PacMan/Gameplay/Entities/Managers/EntitiesManager.h"
#include "PacMan/Gameplay/Ghosts/Managers/GhostsPrisionManager.h"
#include "spdlog/spdlog.h"

namespace PacMan
{
	PlayerDeathManager::PlayerDeathManager(
		GEngine::CoroutinesRunner* coroutines,
		EntitiesManager* entitiesManager,
		GhostsPrisionManager* ghostsPrisionManager,
		PlayerLoaderManager* playerLoaderManager
		)
		: _coroutines(coroutines),
		_entitiesManager(entitiesManager),
		_ghostsPrisionManager(ghostsPrisionManager),
		_playerLoaderManager(playerLoaderManager)
	{
	}

	void PlayerDeathManager::RunDeath()
	{
		_coroutines->Start(&PlayerDeathManager::RunDeathSequenceAsync, this).Forget();
	}

	tokoro::Async<void> PlayerDeathManager::RunDeathSequenceAsync()
	{
		_entitiesManager->StopAllEntitiesMovement();
		_ghostsPrisionManager->Stop();

		_playerLoaderManager->SetPlayerToInitialPosition();

		co_return;
	}
}
