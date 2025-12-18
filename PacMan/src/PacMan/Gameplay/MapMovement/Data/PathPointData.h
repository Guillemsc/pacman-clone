//
// Created by guillem on 12/18/25.
//

#ifndef PATHPOINTDATA_H
#define PATHPOINTDATA_H

#include "glm/fwd.hpp"

namespace PacMan
{
	struct PathPointData
	{
		glm::i32vec2 gridPosition;
		bool fromPortal;
	};
}

#endif //PATHPOINTDATA_H
