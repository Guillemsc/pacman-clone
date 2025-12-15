//
// Created by guillem on 12/13/25.
//

#include "GhostAnimationComponent.h"

namespace PacMan
{
	GhostAnimationComponent::GhostAnimationComponent(
		GEngine::GEngineCoreModules *modules,
		const std::weak_ptr<GEngine::Entity> &entity,
		GhostsStateData *ghostsStateData,
		const std::weak_ptr<GEngine::Sprite2dRendererComponent> &spriteRendererComponent,
		const std::weak_ptr<GEngine::Sprite2dAnimatorComponent> &spriteAnimatorComponent
		) : Component(modules, entity),
		_ghostsStateData(ghostsStateData),
		_spriteRendererComponent(spriteRendererComponent),
		_spriteAnimatorComponent(spriteAnimatorComponent)
	{
	}

	void GhostAnimationComponent::OnTick()
	{

	}
}
