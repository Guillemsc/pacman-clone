//
// Created by guillem on 6/29/25.
//

#include "MapMovementComponent.h"

namespace PacMan
{
	MapMovementComponent::MapMovementComponent(GEngine::GEngineCoreModules* modules, const std::weak_ptr<GEngine::Entity> &entity)
		: Component(modules, entity)
	{
	}
}
