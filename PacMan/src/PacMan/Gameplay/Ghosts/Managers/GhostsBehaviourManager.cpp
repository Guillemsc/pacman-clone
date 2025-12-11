//
// Created by guillem on 12/11/25.
//

#include "GhostsBehaviourManager.h"

#include "PacMan/Gameplay/Ghosts/Data/GhostsStateData.h"

namespace PacMan
{
	GhostsBehaviourManager::GhostsBehaviourManager(GhostsStateData *ghostsStateData)
		: _ghostsStateData(ghostsStateData)
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
	}

	void GhostsBehaviourManager::SetGhostsFrightened() const
	{
		_ghostsStateData->ghostsModeBeforeFrightened = _ghostsStateData->ghostsMode;
		_ghostsStateData->ghostsMode = GhostMode::FRIGHTENED;
		_ghostsStateData->ghostsFrightenedTimer.Restart();
		_ghostsStateData->ghostsScaterChaseTimer.Pause();
	}

	void GhostsBehaviourManager::ResetGhostsState() const
	{
		_ghostsStateData->ghostsMode = GhostMode::SCATTER;
		_ghostsStateData->ghostsScaterChaseTimer.Reset();
	}

	void GhostsBehaviourManager::TickCheckScatterChaseBehaviour() const
	{
		if (_ghostsStateData->ghostsMode == GhostMode::FRIGHTENED) return;

		if (_ghostsStateData->ghostsMode == GhostMode::SCATTER)
		{
			if (_ghostsStateData->ghostsScaterChaseTimer.GetTimeSeconds() > 999)
			{
				_ghostsStateData->ghostsMode = GhostMode::CHASE;
				_ghostsStateData->ghostsScaterChaseTimer.Restart();
			}
		}
		else if (_ghostsStateData->ghostsMode == GhostMode::CHASE)
		{
			if (_ghostsStateData->ghostsScaterChaseTimer.GetTimeSeconds() > 10)
			{
				_ghostsStateData->ghostsMode = GhostMode::SCATTER;
				_ghostsStateData->ghostsScaterChaseTimer.Restart();
			}
		}
	}

	void GhostsBehaviourManager::TickCheckGhostsFrightenedTimeFinished() const
	{
		if (_ghostsStateData->ghostsMode != GhostMode::FRIGHTENED) return;

		const bool timeReached = _ghostsStateData->ghostsFrightenedTimer.GetTimeSeconds() >= 8;

		if (!timeReached) return;

		_ghostsStateData->ghostsMode = _ghostsStateData->ghostsModeBeforeFrightened;
		_ghostsStateData->ghostsScaterChaseTimer.Resume();
	}
}
