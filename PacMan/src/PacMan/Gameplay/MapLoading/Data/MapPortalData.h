//
// Created by guillem on 12/18/25.
//

#ifndef MAPPORTALDATA_H
#define MAPPORTALDATA_H

#include "glm/vec2.hpp"

namespace PacMan
{
	struct MapPortalData
	{
		std::int32_t id;
		glm::i32vec2 gridPosition;
		glm::i32vec2 enterDirection;
		glm::i32vec2 exitDirection;
		std::int32_t connectionId;
		std::int32_t connectedPortalId;
	};
}

#endif //MAPPORTALDATA_H
