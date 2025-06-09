//
// Created by guillem on 6/7/25.
//

#include "Component.h"

namespace GEngineCore
{
	Component::Component(const std::weak_ptr<Entity> &entity)
	{
		_entity = entity;
	}

	Component::~Component()
	{
	}

	std::weak_ptr<Entity> Component::GetEntity() const
	{
		return _entity;
	}

	std::weak_ptr<GEngineCoreApplication> Component::GetApp() const
	{
		std::shared_ptr<Entity> entity = _entity.lock();
		if (!entity) return std::weak_ptr<GEngineCoreApplication>();

		return entity->GetApp();
	}
} // GEngineCore