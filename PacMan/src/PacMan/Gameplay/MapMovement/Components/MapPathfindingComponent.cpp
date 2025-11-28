//
// Created by guillem on 11/27/25.
//

#include "MapPathfindingComponent.h"

namespace PacMan
{
	MapPathfindingComponent::MapPathfindingComponent(GEngine::GEngineCoreModules *modules, const std::weak_ptr<GEngine::Entity> &entity)
		: Component(modules, entity)
	{
	}
}
