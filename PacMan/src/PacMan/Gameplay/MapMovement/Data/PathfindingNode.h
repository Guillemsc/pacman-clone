//
// Created by guillem on 11/27/25.
//

#ifndef PATHFINDINGNODE_H
#define PATHFINDINGNODE_H

#include <memory>

#include "glm/vec2.hpp"

namespace PacMan
{
	struct PathfindingNode
	{
		float priority;
		float distance;
		glm::i32vec2 position = glm::i32vec2(0);
		std::shared_ptr<PathfindingNode> parent;
	};
}

#endif //PATHFINDINGNODE_H
