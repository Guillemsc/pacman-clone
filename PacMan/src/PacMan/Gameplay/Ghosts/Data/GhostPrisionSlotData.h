//
// Created by guillem on 11/28/25.
//

#ifndef GHOSTPRISIONSLOTDATA_H
#define GHOSTPRISIONSLOTDATA_H

#include <memory>

#include "glm/vec2.hpp"

namespace GEngine
{
	class Entity;
}

namespace PacMan
{
	struct GhostPrisionSlotData
	{
		glm::i32vec2 gridPosition;
		std::weak_ptr<GEngine::Entity> ghostEntity;
	};
}

#endif //GHOSTPRISIONSLOTDATA_H
