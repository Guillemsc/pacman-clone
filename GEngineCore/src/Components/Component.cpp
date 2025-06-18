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
		const std::shared_ptr<Entity> entity = _entity.lock();
		if (!entity) return std::weak_ptr<GEngineCoreApplication>();

		return entity->GetApp();
	}

	bool Component::IsEnanbled() const
	{
		return _isEnabledSelf;
	}

	void Component::SetEnabled(const bool enabled)
	{
		_isEnabledSelf = enabled;

		RefreshEnabledState();
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