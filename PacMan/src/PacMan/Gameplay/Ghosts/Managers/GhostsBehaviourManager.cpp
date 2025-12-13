//
// Created by guillem on 12/11/25.
//

#include "GhostsBehaviourManager.h"

#include "GEngine/Entities/Entity.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"
#include "PacMan/Gameplay/Ghosts/Components/GhostAiComponent.h"
#include "PacMan/Gameplay/Ghosts/Data/GhostsStateData.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"

namespace PacMan
{
	GhostsBehaviourManager::GhostsBehaviourManager(
		GhostsStateData *ghostsStateData,
		GameplayEntities* gameplayEntities
		)
		: _ghostsStateData(ghostsStateData),
		_gameplayEntities(gameplayEntities)
	{
	}

	void GhostsBehaviourManager::Tick()
	{
		TickCheckScatterChaseBehaviour();
		TickCheckGhostsFrightenedTimeFinished();
	}

	void GhostsBehaviourManager::StartGhostsBehaviours() const
	{
		_ghostsStateData->ghostsScaterChaseTimer.Start();
		SetNonDeathGhostsMovementSpeed(_initialGhostsMovementSpeed);
	}

	void GhostsBehaviourManager::ResetGhostsBehavioursState() const
	{
		_ghostsStateData->ghostsMode = GhostMode::SCATTER;
		_ghostsStateData->ghostsScaterChaseTimer.Reset();

		SetNonDeathGhostsMovementSpeed(_initialGhostsMovementSpeed);
	}

	void GhostsBehaviourManager::SetGhostsFrightened() const
	{
		_ghostsStateData->ghostsModeBeforeFrightened = _ghostsStateData->ghostsMode;
		_ghostsStateData->ghostsMode = GhostMode::FRIGHTENED;
		_ghostsStateData->ghostsFrightenedTimer.Restart();
		_ghostsStateData->ghostsScaterChaseTimer.Pause();

		SetNonDeathGhostsMovementSpeed(15);
	}

	void GhostsBehaviourManager::TickCheckScatterChaseBehaviour() const
	{
		if (_ghostsStateData->ghostsMode == GhostMode::FRIGHTENED) return;

		if (_ghostsStateData->ghostsMode == GhostMode::SCATTER)
		{
			if (_ghostsStateData->ghostsScaterChaseTimer.GetTimeSeconds() > 7)
			{
				_ghostsStateData->ghostsMode = GhostMode::CHASE;
				_ghostsStateData->ghostsScaterChaseTimer.Restart();
			}
		}
		else if (_ghostsStateData->ghostsMode == GhostMode::CHASE)
		{
			if (_ghostsStateData->ghostsScaterChaseTimer.GetTimeSeconds() > 20)
			{
				_ghostsStateData->ghostsMode = GhostMode::SCATTER;
				_ghostsStateData->ghostsScaterChaseTimer.Restart();
			}
		}
	}

	void GhostsBehaviourManager::TickCheckGhostsFrightenedTimeFinished() const
	{
		if (_ghostsStateData->ghostsMode != GhostMode::FRIGHTENED) return;

		const bool timeReached = _ghostsStateData->ghostsFrightenedTimer.GetTimeSeconds() >= 10;

		if (!timeReached) return;

		_ghostsStateData->ghostsMode = _ghostsStateData->ghostsModeBeforeFrightened;
		_ghostsStateData->ghostsScaterChaseTimer.Resume();

		SetNonDeathGhostsMovementSpeed(_initialGhostsMovementSpeed);
	}

	void GhostsBehaviourManager::SetNonDeathGhostsMovementSpeed(const float speed) const
	{
		for (std::weak_ptr<GEngine::Entity> entry : _gameplayEntities->Ghosts)
		{
			const std::shared_ptr<GEngine::Entity> entity = entry.lock();
			if (!entity) continue;

			const std::shared_ptr<MapMovementComponent> mapMovement = entity->GetComponent<MapMovementComponent>().lock();
			if (!mapMovement) continue;

			mapMovement->SetMovementSpeed(speed);
		}
	}
}
