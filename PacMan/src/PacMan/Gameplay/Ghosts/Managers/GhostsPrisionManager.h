//
// Created by guillem on 11/28/25.
//

#ifndef GHOSTSPRISIONMANAGER_H
#define GHOSTSPRISIONMANAGER_H

#include <vector>

#include "tokoro.h"
#include "GEngine/Coroutines/CancellationToken.h"
#include "GEngine/Tickables/Tickable.h"
#include "GEngine/Timers/ChronoTimer.h"
#include "glm/vec2.hpp"
#include "PacMan/Gameplay/Ghosts/Data/LoadedGhostsData.h"

namespace GEngine
{
	class Tween;
	class CoroutinesRunner;
	class GEngineCoreModules;
	class Entity;
}

namespace PacMan
{
	struct GhostsStateData;
	class MapMovementManager;
	struct LoadedMapData;
}

namespace PacMan
{
	struct LoadedGhostsData;
	struct GhostPrisionSlotData;
	struct GhostsPrisionData;

	class GhostsPrisionManager final : public GEngine::Tickable
	{
	public:
		GhostsPrisionManager(
			GEngine::GEngineCoreModules* modules,
			GEngine::CoroutinesRunner* coroutines,
			MapMovementManager* mapMovementManager,
			GhostsStateData* ghostsStateData
			);

		void Tick() override;

		void Setup(const LoadedMapData& loadedMapData, const LoadedGhostsData& loadedGhostsData);

		void Stop();
		void Reset();

		void TryKillGhostAndStartPathBackToPrision(const std::weak_ptr<GEngine::Entity> &ghost);

	private:
		void StartGhostPrisionAnimation(const std::weak_ptr<GEngine::Entity> &ghost);
		void ReleaseNextGhost();
		GhostPrisionSlotData* GetNextSlotToReleaseOrNull() const;
		tokoro::Async<void> PlayReleaseGhostAsync(
			std::shared_ptr<GEngine::Entity> ghostEntity,
			GEngine::CancellationToken cancellationToken
			);
		tokoro::Async<void> PlayReturnGhostAsync(
			std::shared_ptr<GEngine::Entity> ghostEntity,
			GEngine::CancellationToken cancellationToken
			);

	private:
		GEngine::GEngineCoreModules* const _modules;
		GEngine::CoroutinesRunner* const _coroutines;
		MapMovementManager* const _mapMovementManager;
		GhostsStateData* const _ghostsStateData;

		LoadedGhostsData _loadedGhostsData;

		std::unique_ptr<GhostPrisionSlotData> _leftSlot;
		std::unique_ptr<GhostPrisionSlotData> _centerSlot;
		std::unique_ptr<GhostPrisionSlotData> _rightSlot;

		std::shared_ptr<GEngine::CancellationTokenSource> _cancellationTokenSource;

		glm::i32vec2 _prisionExitGridPosition = glm::i32vec2(0);
		glm::vec2 _prisionExitPosition = glm::vec2(0);
		glm::vec2 _prisionReturnPosition = glm::vec2(0);

		GEngine::ChronoTimer _timeSinceLastGhostReleasedTimer;
	};
}

#endif //GHOSTSPRISIONMANAGER_H
