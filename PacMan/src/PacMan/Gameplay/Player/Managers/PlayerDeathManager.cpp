//
// Created by guillem on 12/5/25.
//

#include "PlayerDeathManager.h"

#include "PlayerLoaderManager.h"
#include "GEngine/Coroutines/CoroutinesRunner.h"
#include "GEngine/Logging/GEngineLog.h"
#include "PacMan/Gameplay/Entities/Managers/EntitiesManager.h"
#include "PacMan/Gameplay/Ghosts/Managers/GhostsBehaviourManager.h"
#include "PacMan/Gameplay/Ghosts/Managers/GhostsLoadingManager.h"
#include "PacMan/Gameplay/Ghosts/Managers/GhostsPrisionManager.h"
#include "spdlog/spdlog.h"

namespace PacMan
{
	PlayerDeathManager::PlayerDeathManager(
		GEngine::CoroutinesRunner* coroutines,
		EntitiesManager* entitiesManager,
		GhostsPrisionManager* ghostsPrisionManager,
		PlayerLoaderManager* playerLoaderManager,
		GhostsLoadingManager* ghostsLoadingManager,
		GhostsBehaviourManager* ghostsBehaviourManager
		)
		: _coroutines(coroutines),
		_entitiesManager(entitiesManager),
		_ghostsPrisionManager(ghostsPrisionManager),
		_playerLoaderManager(playerLoaderManager),
		_ghostsLoadingManager(ghostsLoadingManager),
		_ghostsBehaviourManager(ghostsBehaviourManager)
	{
	}

	void PlayerDeathManager::RunDeath()
	{
		_coroutines->Start(&PlayerDeathManager::RunDeathSequenceAsync, this).Forget();
	}

	tokoro::Async<void> PlayerDeathManager::RunDeathSequenceAsync() const
	{
		GGAME_INFO("Starting death sequence.");

		_ghostsBehaviourManager->ResetGhostsState();
		_entitiesManager->StopAllEntitiesMovement();
		_ghostsPrisionManager->Stop();

		_playerLoaderManager->SetPlayerToInitialPosition();
		_ghostsLoadingManager->SetGhostsToInitialPosition();

		co_await GEngine::ChronoTimer::AwaitSeconds(1, GEngine::CancellationToken::None());

		_ghostsPrisionManager->Reset();
		_entitiesManager->StartPlayerAndMapGhostEntitiesMovement();
		_ghostsBehaviourManager->StartGhostsBehaviours();

		co_return;
	}
}
