//
// Created by guillem on 12/10/25.
//

#ifndef GHOSTSSTATEDATA_H
#define GHOSTSSTATEDATA_H

#include "GEngine/Timers/ChronoTimer.h"
#include "PacMan/Gameplay/Ghosts/Enums/GhostMode.h"

namespace PacMan
{
	struct GhostsStateData
	{
		GhostMode ghostsMode = GhostMode::SCATTER;
		GEngine::ChronoTimer ghostsScaterChaseTimer;

		GEngine::ChronoTimer ghostsFrightenedTimer;
		GhostMode ghostsModeBeforeFrightened = GhostMode::SCATTER;
	};
}

#endif //GHOSTSSTATEDATA_H
