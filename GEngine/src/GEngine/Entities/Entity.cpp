//
// Created by guillem on 6/8/25.
//

#include "Entity.h"

#include "EntityHierarchyIterator.h"
#include "GEngine/Components/Component.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Extensions/VectorExtensions.h"
#include "GEngine/Modules/EntitiesModule.h"
#include "GEngine/Modules/GuizmosModule.h"
#include "GEngine/Pooling/Pools.h"

namespace GEngine
{
	Entity::Entity(GEngineCoreModules* modules, const std::uint32_t id)
		: modules(modules), _id(id)
	{

	}

	Entity::~Entity()
	{
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

	bool Entity::IsAlive() const
	{
		return _isAlive;
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

	std::uint32_t Entity::GetRenderingPositionInHierarchy() const
	{
		return _renderingPositionInHierarchy;
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

			checking = checking->_parent.lock();
		}

		return false;
	}

	void Entity::SetParent(const std::weak_ptr<Entity> &parentEntity, const bool worldPositionStays)
	{
		modules->entities->SetEntityParent(weak_from_this(), parentEntity, worldPositionStays);
	}

	void Entity::RemoveParent(const bool worldPositionStays)
	{
		modules->entities->RemoveEntityParent(weak_from_this(), worldPositionStays);
	}

	std::weak_ptr<Entity> Entity::GetParent() const
	{
		return _parent;
	}

	const std::vector<std::weak_ptr<Entity>>& Entity::GetChildren() const
	{
		return _childEntities;
	}

	const std::vector<std::shared_ptr<Component>> & Entity::GetComponents() const
	{
		return _components;
	}

	bool Entity::RemoveComponent(const std::weak_ptr<Component> &componentPtr)
	{
		const std::shared_ptr<Component> component = componentPtr.lock();
		if (!component) return false;

		for (auto it = _components.begin(); it != _components.end(); ++it)
		{
			if (it->get() == component.get())
			{
				(*it)->SetEnabled(false);
				(*it)->OnDestroy();
				_components.erase(it);
				return true;
			}
		}

		return false;
	}

	std::weak_ptr<TransformComponent> Entity::GetTransform() const
	{
		return _transformComponent;
	}

	std::weak_ptr<UiTransformComponent> Entity::GetUiTransform() const
	{
		return _uiTransformComponent;
	}

	void GEngine::Entity::Dispose()
	{
		RemoveAllComponents();

		_id = 0;
		_parent.reset();
		_childEntities.clear();
		_components.clear();
		_transformComponent.reset();
	}

	void Entity::TickAllComponents()
	{
		for (auto it = _components.begin(); it != _components.end(); ++it)
		{
			if (!(*it)->_isEnabledInHierarchy) continue;

			(*it)->OnTick();
			modules->guizmos->DrawComponentGuizmo(it->get());
		}
	}

	void Entity::RemoveAllComponents()
	{
		for (auto it = _components.begin(); it != _components.end(); ++it)
		{
			(*it)->SetEnabled(false);
			(*it)->OnDestroy();
		}

		_components.clear();
	}

	void Entity::RefreshChildrenHierarchyActiveState()
	{
		EntityHierarchyIterator entityHierarchyIterator(weak_from_this());

		while (entityHierarchyIterator.HasNext())
		{
			Entity* checkingEntity = entityHierarchyIterator.GetNext(false);
			if (!checkingEntity) break;

			const bool stateChanged = checkingEntity->RefreshActiveState();

			if (stateChanged)
			{
				entityHierarchyIterator.AddCurrentChildren();
			}
		}
	}

	bool Entity::RefreshActiveState()
	{
		bool parentIsActive = true;

		const std::shared_ptr<Entity> parent = _parent.lock();

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
