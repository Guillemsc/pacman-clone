//
// Created by guillem on 12/3/25.
//

#ifndef COLLISIONLAYERS_H
#define COLLISIONLAYERS_H

#include <cstdint>

namespace PacMan
{
	enum CollisionLayers : std::uint32_t
	{
		COLLISION_LAYER_DEFAULT   = 1 << 0,
		COLLISION_LAYER_PLAYER    = 1 << 1,
		COLLISION_LAYER_GHOST     = 1 << 2,
		COLLISION_LAYER_PELLETS   = 1 << 3,
	};
}

#endif //COLLISIONLAYERS_H
