//
// Created by guillem on 11/25/25.
//

#ifndef LOADEDMAPDATA_H
#define LOADEDMAPDATA_H

#include "MapPortalData.h"
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
		glm::vec2 MapBounds = glm::vec2(0);
		std::vector<MapPortalData> MapPortals;
		glm::i32vec2 PlayerPosition = glm::i32vec2(0, 0);
		glm::i32vec2 MapGhostPosition = glm::i32vec2(0, 0);
		glm::i32vec2 GhostPrisionLeftSlotGridPosition = glm::i32vec2(0, 0);
		glm::i32vec2 GhostPrisionCenterSlotGridPosition = glm::i32vec2(0, 0);
		glm::i32vec2 GhostPrisionRightSlotGridPosition = glm::i32vec2(0, 0);
		glm::i32vec2 PrisionExitPosition = glm::i32vec2(0, 0);
		std::vector<glm::i32vec2> SmallPelletsPositions;
		std::vector<glm::i32vec2> BigPelletsPositions;
	};
}

#endif //LOADEDMAPDATA_H
