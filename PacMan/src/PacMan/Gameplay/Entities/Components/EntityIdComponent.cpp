//
// Created by guillem on 12/3/25.
//

#include "EntityIdComponent.h"

namespace PacMan
{
	EntityIdComponent::EntityIdComponent(GEngine::GEngineCoreModules *modules, const std::weak_ptr<GEngine::Entity> &entity)
		: Component(modules, entity)
	{
	}

	void EntityIdComponent::SetType(const EntityType type)
	{
		_type = type;
	}
}
