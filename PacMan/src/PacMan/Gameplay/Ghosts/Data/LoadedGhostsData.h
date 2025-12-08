//
// Created by guillem on 11/28/25.
//

#ifndef LOADEDGHOSTSDATA_H
#define LOADEDGHOSTSDATA_H
#include <memory>

namespace GEngine
{
	class Entity;
}

namespace PacMan {

struct LoadedGhostsData
{
	std::weak_ptr<GEngine::Entity> MapGhostEntity;
	std::weak_ptr<GEngine::Entity> LeftPrisionSlotGhostEntity;
	std::weak_ptr<GEngine::Entity> CenterPrisionSlotGhostEntity;
	std::weak_ptr<GEngine::Entity> RightPrisionSlotGhostEntity;
};

} // PacMan

#endif //LOADEDGHOSTSDATA_H
