//
// Created by guillem on 11/27/25.
//

#ifndef PATHFINDINGNODE_H
#define PATHFINDINGNODE_H

#include <memory>

#include "glm/vec2.hpp"
#include "PacMan/Gameplay/MapMovement/Data/PathPointData.h"

namespace PacMan
{
	struct PathfindingNode
	{
		float priority;
		float distance;
		PathPointData pathPoint;
		std::shared_ptr<PathfindingNode> parent;
	};
}

#endif //PATHFINDINGNODE_H
