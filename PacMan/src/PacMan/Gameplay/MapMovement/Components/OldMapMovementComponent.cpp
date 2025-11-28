//
// Created by guillem on 6/29/25.
//

#include "OldMapMovementComponent.h"

namespace PacMan
{
	OldMapMovementComponent::OldMapMovementComponent(GEngine::GEngineCoreModules* modules, const std::weak_ptr<GEngine::Entity> &entity)
		: Component(modules, entity)
	{
	}
}
