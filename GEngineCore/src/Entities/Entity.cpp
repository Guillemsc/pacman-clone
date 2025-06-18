//
// Created by guillem on 6/8/25.
//

#include "Entity.h"

#include "Components/Component.h"
#include "Core/GEngineCoreApplication.h"
#include "Modules/ComponentsModule.h"
#include "Modules/EntitiesModule.h"

namespace GEngineCore
{
	Entity::Entity(const std::weak_ptr<GEngineCoreApplication> &appPtr, const std::uint32_t id)
	{
		_appPtr = appPtr;
		_id = id;
	}

	Entity::~Entity()
	{
	}

	std::weak_ptr<GEngineCoreApplication> Entity::GetApp() const
	{
		return _appPtr;
	}

	std::uint32_t Entity::GetId() const
	{
		return _id;
	}

	void Entity::SetName(const std::string &name)
	{
		if (name.empty())
		{
			return;
		}

		_name = name;
	}

	std::string Entity::GetName() const
	{
		return _name;
	}

	bool Entity::IsActiveSelf() const
	{
		return _isActiveSelf;
	}

	bool Entity::IsActiveInHierarchy() const
	{
		return _isActiveInHierarchy;
	}

	void Entity::SetActive(const bool active)
	{
		_isActiveSelf = active;

		RefreshChildrenHierarchyActiveState();
	}

	bool Entity::IsInsideChildHierarchy(const std::weak_ptr<Entity> &checkingPtr) const
	{
		std::shared_ptr<Entity> checking = checkingPtr.lock();

		while (checking != nullptr)
		{
			if (checking.get() == this)
			{
				return true;
			}

			checking = checking->_parentPtr.lock();
		}

		return false;
	}

	void Entity::SetParent(const std::weak_ptr<Entity> &parentPtr, bool worldPositionStays)
	{
		const std::shared_ptr<GEngineCoreApplication> app = _appPtr.lock();
		if (app == nullptr) return;

		const std::shared_ptr<EntitiesModule> entities = app->Entities().lock();
		if (entities == nullptr) return;

		entities->SetEntityParent(weak_from_this(), parentPtr, worldPositionStays);
	}

	void Entity::RemoveParent(bool worldPositionStays)
	{
		const std::shared_ptr<GEngineCoreApplication> app = _appPtr.lock();
		if (app == nullptr) return;

		const std::shared_ptr<EntitiesModule> entities = app->Entities().lock();
		if (entities == nullptr) return;

		entities->RemoveEntityParent(weak_from_this(), worldPositionStays);
	}

	void Entity::ForEachEntityInChildHierarchy(
		const bool includeCurrent,
		const std::function<bool(const std::shared_ptr<Entity>&)> &callback
		)
	{
		// TODO: Pool this vector
		std::vector<std::shared_ptr<Entity>> toCheck;
		toCheck.push_back(shared_from_this());

		bool firstChecking = true;

		while (toCheck.size() > 0)
		{
			std::shared_ptr<Entity> checking = toCheck.front();
			toCheck.erase(toCheck.begin());

			bool shouldAddChildren = true;

			if (includeCurrent || !firstChecking)
			{
				shouldAddChildren = callback(checking);
			}

			if (shouldAddChildren)
			{
				for (auto it = checking->GetChildren().begin(); it != checking->GetChildren().end(); ++it)
				{
					const std::shared_ptr<Entity> childEntity = it->lock();
					if (!childEntity) continue;

					toCheck.push_back(childEntity);
				}
			}

			firstChecking = false;
		}
	}

	std::weak_ptr<Entity> Entity::GetParent() const
	{
		return _parentPtr;
	}

	const std::vector<std::weak_ptr<Entity>>& Entity::GetChildren() const
	{
		return _childEntities;
	}

	const std::vector<std::shared_ptr<Component>> & Entity::GetComponents() const
	{
		return _components;
	}

	std::weak_ptr<Component> Entity::GetComponent(const ComponentType componentType)
	{
		for (auto it = _components.begin(); it != _components.end(); ++it)
		{
			if ((*it)->GetType() == componentType)
			{
				return *it;
			}
		}

		return std::weak_ptr<Component>();
	}

	std::weak_ptr<Component> Entity::AddComponent(const ComponentType componentType)
	{
		const std::shared_ptr<GEngineCoreApplication> app = _appPtr.lock();
		if (app == nullptr) return std::weak_ptr<Component>();

		const std::shared_ptr<ComponentsModule> components = app->Components().lock();
		if (components == nullptr) return std::weak_ptr<Component>();

		return components->AddEntityComponent(weak_from_this(), componentType);
	}

	std::weak_ptr<TransformComponent> Entity::GetTransform() const
	{
		return _transformPtr;
	}

	void GEngineCore::Entity::Dispose()
	{
		_id = 0;
		_parentPtr.reset();
		_childEntities.clear();
		_components.clear();
		_transformPtr.reset();
	}

	void Entity::RefreshChildrenHierarchyActiveState()
	{
		ForEachEntityInChildHierarchy(true, [](const std::shared_ptr<Entity> &checking)
		{
			return checking->RefreshActiveState();
		});
	}

	bool Entity::RefreshActiveState()
	{
		bool parentIsActive = true;

		const std::shared_ptr<Entity> parent = _parentPtr.lock();

		if (parent)
		{
			parentIsActive = parent->IsActiveInHierarchy();
		}

		const bool shouldBeActive = parentIsActive && _isActiveSelf;

		if (shouldBeActive == _isActiveInHierarchy)
		{
			return false;
		}

		_isActiveInHierarchy = shouldBeActive;

		for (auto it = _components.begin(); it != _components.end(); ++it)
		{
			(*it)->RefreshEnabledState();
		}

		return true;
	}
}
