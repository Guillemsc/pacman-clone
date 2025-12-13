//
// Created by guillem on 12/13/25.
//

#include "GhostAnimationComponent.h"

namespace PacMan
{
	GhostAnimationComponent::GhostAnimationComponent(
		GEngine::GEngineCoreModules *modules,
		const std::weak_ptr<GEngine::Entity> &entity,
		GhostsStateData *ghostsStateData
		) : Component(modules, entity),
		_ghostsStateData(ghostsStateData)
	{
	}
}
