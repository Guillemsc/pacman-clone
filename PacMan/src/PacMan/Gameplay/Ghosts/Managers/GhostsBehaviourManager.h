//
// Created by guillem on 12/11/25.
//

#ifndef GHOSTSBEHAVIOURMANAGER_H
#define GHOSTSBEHAVIOURMANAGER_H

#include <memory>
#include <vector>

#include "GEngine/Tickables/Tickable.h"

namespace GEngine
{
	class Entity;
}

namespace PacMan
{
	class GameplayEntities;
}

namespace PacMan
{
	struct GhostsStateData;

	class GhostsBehaviourManager final : public GEngine::Tickable
	{
	public:
		explicit GhostsBehaviourManager(
			GhostsStateData* ghostsStateData,
			GameplayEntities* gameplayEntities
			);

		void Tick() override;

		void StartGhostsBehaviours() const;
		void ResetGhostsBehavioursState() const;
		void SetGhostsFrightened() const;

	private:
		void TickCheckScatterChaseBehaviour() const;
		void TickCheckGhostsFrightenedTimeFinished() const;
		void SetNonDeathGhostsMovementSpeed(float speed) const;

	private:
		GhostsStateData* const _ghostsStateData;
		GameplayEntities* const _gameplayEntities;

		float _initialGhostsMovementSpeed = 40;
	};
}

#endif //GHOSTSBEHAVIOURMANAGER_H
