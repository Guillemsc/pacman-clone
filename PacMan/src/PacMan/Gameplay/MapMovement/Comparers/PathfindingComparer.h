//
// Created by guillem on 11/27/25.
//

#ifndef PATHFINDINGCOMPARER_H
#define PATHFINDINGCOMPARER_H

#include "PacMan/Gameplay/MapMovement/Data/PathfindingNode.h"

namespace PacMan
{
	class PathfindingComparer
	{
	public:
		bool operator()(const std::shared_ptr<PathfindingNode>& a, const std::shared_ptr<PathfindingNode>& b) const
		{
			return a->distance > b->distance;
		}
	};
}

#endif //PATHFINDINGCOMPARER_H
