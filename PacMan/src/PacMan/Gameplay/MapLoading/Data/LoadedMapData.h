//
// Created by guillem on 11/25/25.
//

#ifndef LOADEDMAPDATA_H
#define LOADEDMAPDATA_H

#include "glm/vec2.hpp"

namespace PacMan
{
	struct LoadedMapData
	{
		glm::i32vec2 PlayerPosition = glm::i32vec2(0, 0);
		glm::i32vec2 RedGhostPosition = glm::i32vec2(0, 0);
		glm::i32vec2 CianGhostPosition = glm::i32vec2(0, 0);
		glm::i32vec2 PinkGhostPosition = glm::i32vec2(0, 0);
		glm::i32vec2 OrangeGhostPosition = glm::i32vec2(0, 0);
	};
}

#endif //LOADEDMAPDATA_H
