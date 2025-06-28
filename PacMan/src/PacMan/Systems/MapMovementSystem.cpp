//
// Created by guillem on 6/28/25.
//

#include "MapMovementSystem.h"

namespace Pacman
{
	MapMovementSystem::MapMovementSystem(
		const std::weak_ptr<GEngine::Entity> &entity,
		const std::weak_ptr<GEngine::TiledMap2dRendererComponent> &tileComponent
		)
	{
		_entity = entity;
		_tileComponent = tileComponent;
	}

	void MapMovementSystem::Tick()
	{

	}
}
