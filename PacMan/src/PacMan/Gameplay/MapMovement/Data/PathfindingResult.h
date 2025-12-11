//
// Created by guillem on 12/11/25.
//

#ifndef PATHFINDINGRESULT_H
#define PATHFINDINGRESULT_H

#include "glm/vec2.hpp"

namespace PacMan
{
	struct PathfindingResult
	{
		bool couldReachAnyPosition = false;
		bool couldReachTarget = false;
		glm::i32vec2 realTargetGridPosition = glm::i32vec2(0);
	};
}

#endif //PATHFINDINGRESULT_H
