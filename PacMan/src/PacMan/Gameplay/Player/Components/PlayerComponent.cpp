//
// Created by guillem on 11/27/25.
//

#include "PlayerComponent.h"

namespace PacMan
{
	PlayerComponent::PlayerComponent(GEngine::GEngineCoreModules *modules, const std::weak_ptr<GEngine::Entity> &entity)
		: Component(modules, entity)
	{
	}
}
