//
// Created by guillem on 7/28/25.
//

#ifndef MAPMOVEMENTMANAGER_H
#define MAPMOVEMENTMANAGER_H

#include <memory>

#include "GEngine/Resources/TiledMapResource.h"

namespace PacMan
{
	class MapMovementManager
	{
	private:
		std::weak_ptr<GEngine::TiledMapResource> _tiledMap;
		int _walkabilityLayerIndex = 0;
	};
}

#endif //MAPMOVEMENTMANAGER_H
