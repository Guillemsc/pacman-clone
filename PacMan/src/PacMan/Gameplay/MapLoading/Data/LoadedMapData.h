//
// Created by guillem on 11/25/25.
//

#ifndef LOADEDMAPDATA_H
#define LOADEDMAPDATA_H

#include "glm/vec2.hpp"

namespace GEngine
{
	class TiledMap2dRendererComponent;
}

namespace PacMan
{
	struct LoadedMapData
	{
		std::weak_ptr<GEngine::TiledMap2dRendererComponent> Tilemap;
		glm::i32vec2 PlayerPosition = glm::i32vec2(0, 0);
		glm::i32vec2 RedGhostPosition = glm::i32vec2(0, 0);
		glm::i32vec2 GhostPrisionLeftSlotPosition = glm::i32vec2(0, 0);
		glm::i32vec2 GhostPrisionCenterSlotPosition = glm::i32vec2(0, 0);
		glm::i32vec2 GhostPrisionRightSlotPosition = glm::i32vec2(0, 0);
		glm::i32vec2 PrisionExitPosition = glm::i32vec2(0, 0);
		std::vector<glm::i32vec2> SmallPelletsPositions;
	};
}

#endif //LOADEDMAPDATA_H
