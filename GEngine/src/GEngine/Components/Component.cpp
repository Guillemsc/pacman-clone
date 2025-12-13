//
// Created by guillem on 6/7/25.
//

#include "Component.h"

namespace GEngine
{
	Component::Component(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity)
		: modules(modules), _entity(entity)
	{

	}

	std::weak_ptr<Entity> Component::GetEntity() const
	{
		return _entity;
	}

	void Component::SetEnabled(const bool enabled)
	{
		_isEnabledSelf = enabled;

		RefreshEnabledState();
	}

	bool Component::IsEnabled() const
	{
		return _isEnabledSelf;
	}

	void Component::RefreshEnabledState()
	{
		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return;

		const bool shouldBeEnabled = entity->IsActiveInHierarchy() && _isEnabledSelf;

		if (shouldBeEnabled == _isEnabledInHierarchy)
		{
			return;
		}

		_isEnabledInHierarchy = shouldBeEnabled;

		if (_isEnabledInHierarchy)
		{
			OnEnable();
		}
		else
		{
			OnDisable();
		}
	}
} // GEngineCore