//
// Created by guillem on 12/11/25.
//

#ifndef GHOSTSBEHAVIOURMANAGER_H
#define GHOSTSBEHAVIOURMANAGER_H

#include "GEngine/Tickables/Tickable.h"

namespace PacMan
{
	struct GhostsStateData;

	class GhostsBehaviourManager final : public GEngine::Tickable
	{
	public:
		explicit GhostsBehaviourManager(
			GhostsStateData* ghostsStateData
			);

		void Tick() override;

		void StartGhostsBehaviours() const;
		void SetGhostsFrightened() const;
		void ResetGhostsState() const;

	private:
		void TickCheckScatterChaseBehaviour() const;
		void TickCheckGhostsFrightenedTimeFinished() const;

	private:
		GhostsStateData* const _ghostsStateData;
	};
}

#endif //GHOSTSBEHAVIOURMANAGER_H
