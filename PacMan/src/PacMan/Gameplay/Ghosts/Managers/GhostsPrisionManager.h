//
// Created by guillem on 11/28/25.
//

#ifndef GHOSTSPRISIONMANAGER_H
#define GHOSTSPRISIONMANAGER_H

#include <vector>

#include "GEngine/Timers/ChronoTimer.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	class GEngineCoreModules;
	class Entity;
}

namespace PacMan
{
	class MapMovementManager;
	struct LoadedMapData;
}

namespace PacMan
{
	struct LoadedGhostsData;
	struct GhostPrisionSlotData;
	struct GhostsPrisionData;

	class GhostsPrisionManager
	{
	public:
		GhostsPrisionManager(
			GEngine::GEngineCoreModules* modules,
			MapMovementManager* mapMovementManager
			);

		void Setup(const LoadedMapData& loadedMapData, const LoadedGhostsData& loadedGhostsData);

	private:
		void ReleaseNextGhost();
		GhostPrisionSlotData* GetNextSlotToReleaseOrNull() const;
		void PlayReleaseGhost(const std::shared_ptr<GEngine::Entity> &ghostEntity);

	private:
		GEngine::GEngineCoreModules* const _modules;
		MapMovementManager* const _mapMovementManager;

		std::unique_ptr<GhostPrisionSlotData> _leftSlot;
		std::unique_ptr<GhostPrisionSlotData> _centerSlot;
		std::unique_ptr<GhostPrisionSlotData> _rightSlot;

		glm::i32vec2 _prisionExitGridPosition = glm::i32vec2(0);
		glm::vec2 _prisionExitPosition = glm::vec2(0);

		GEngine::ChronoTimer _timeSinceLastGhostReleasedTimer;
	};
}

#endif //GHOSTSPRISIONMANAGER_H
