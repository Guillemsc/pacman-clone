//
// Created by guillem on 12/18/25.
//

#ifndef RENDERINGLAYER_H
#define RENDERINGLAYER_H

#include <cstdint>

namespace PacMan
{
	enum class RenderingLayer : std::uint8_t
	{
		MAP = 1,
		PELLETS = 3,
		GHOSTS = 4,
		PLAYER = 5,
	};
}

#endif //RENDERINGLAYER_H
