//
// Created by guillem on 6/6/25.
//

#include "EntitiesModule.h"

#include <format>

#include "GEngine/Entities/Entity.h"
#include "GEngine/Extensions/VectorExtensions.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Components/UiTransformComponent.h"
#include "spdlog/spdlog.h"

namespace GEngine
{
	EntitiesModule::EntitiesModule()
	{

	}

	void EntitiesModule::Init(const std::weak_ptr<GEngineCoreApplication> &app)
	{
		_appPtr = app;
	}

	void EntitiesModule::Tick()
	{
		TickEntities();
		ActuallyRemoveEntities();
	}

	void EntitiesModule::Dispose()
	{
		RemoveAllEntitiesNow();
	}

	std::weak_ptr<Entity> EntitiesModule::AddWorldEntity()
	{
		std::shared_ptr<Entity> entity = AddEntity();
		if (!entity) return std::weak_ptr<Entity>();

		entity->AddComponent<TransformComponent>();

		return entity;
	}

	std::weak_ptr<Entity> EntitiesModule::AddUiEntity()
	{
		std::shared_ptr<Entity> entity = AddEntity();
		if (!entity) return std::weak_ptr<Entity>();

		entity->AddComponent<UiTransformComponent>();

		return entity;
	}

	bool EntitiesModule::RemoveEntity(const std::weak_ptr<Entity> &entityPtr)
	{
		const std::shared_ptr<Entity> entity = entityPtr.lock();
		if (entity == nullptr) return false;

		if (!entity->_isAlive)
		{
			return false;
		}

		entity->ForEachEntityInChildHierarchy(true, [](const std::shared_ptr<Entity>& childEntity)
		{
			childEntity->_isAlive = false;
			return true;
		});

		_entitiesToRemove.push_back(entity);

		return true;
	}

	bool EntitiesModule::RemoveEntityNow(const std::weak_ptr<Entity> &entityPtr)
	{
		const std::shared_ptr<GEngineCoreApplication> app = _appPtr.lock();
		if (app == nullptr) return false;

		const std::shared_ptr<Entity> entity = entityPtr.lock();
		if (entity == nullptr) return false;

		if (entity->_parentPtr.lock())
		{
			entity->RemoveParent();
		}
		else
		{
			VectorExtensions::Remove(_rootEntities, entity);
		}

		_checkingRemovingEntitiesBuffer.clear();

		_checkingRemovingEntitiesBuffer.push_back(entity);

		while (_checkingRemovingEntitiesBuffer.size() > 0)
		{
			const std::shared_ptr<Entity> checking = _checkingRemovingEntitiesBuffer.front();
			_checkingRemovingEntitiesBuffer.erase(_checkingRemovingEntitiesBuffer.begin());

			for (auto it = checking->_childEntities.begin(); it != checking->_childEntities.end(); ++it)
			{
				const std::shared_ptr<Entity> child = it->lock();
				if (child == nullptr) continue;

				_checkingRemovingEntitiesBuffer.push_back(child);
			}

			checking->Dispose();

			VectorExtensions::Remove(_entities, checking);
		}

		return true;
	}

	void EntitiesModule::RemoveAllEntitiesNow()
	{
		while (_rootEntities.size() > 0)
		{
			std::weak_ptr<Entity> entityPtr = _rootEntities.front();

			if (entityPtr.expired()) continue;
			std::shared_ptr<Entity> entity = entityPtr.lock();

			RemoveEntityNow(entity);

			std::weak_ptr expiredCheck = entity;
			entity.reset();
		}
	}

	void EntitiesModule::SetEntityParent(
		const std::weak_ptr<Entity> &targetPtr,
		const std::weak_ptr<Entity> &parentPtr,
		const bool worldPositionStays
		)
	{
		const std::shared_ptr<GEngineCoreApplication> app = _appPtr.lock();
		if (app == nullptr) return;

		const std::shared_ptr<Entity> target = targetPtr.lock();
		if (target == nullptr) return;

		const std::shared_ptr<Entity> parent = parentPtr.lock();
		if (parent == nullptr) return;

		const bool isInsideChildHierarchy = parent->IsInsideChildHierarchy(target);

		if (isInsideChildHierarchy)
		{
			return;
		}

		if (!target->_parentPtr.expired())
		{
			RemoveEntityParent(target);
		}

		target->_parentPtr = parent;
		parent->_childEntities.push_back(target);

		VectorExtensions::Remove(_rootEntities, target);

		if (const auto targetTransform = target->GetTransform().lock())
		{
			if (worldPositionStays)
			{
				targetTransform->SetLocalPositionAsWorldPosition();
			}

			targetTransform->RecalculateChildrenHierarchyWorldMatrices();
		}

		if (const auto targetTransform = target->GetUiTransform().lock())
		{
			if (worldPositionStays)
			{
				//targetTransform->SetLocalPositionAsWorldPosition();
			}

			targetTransform->RecalculateChildrenHierarchyWorldUiRects();
		}

		target->RefreshActiveState();
	}

	void EntitiesModule::RemoveEntityParent(const std::weak_ptr<Entity> &targetPtr, const bool worldPositionStays)
	{
		const std::shared_ptr<GEngineCoreApplication> app = _appPtr.lock();
		if (app == nullptr) return;

		const std::shared_ptr<Entity> target = targetPtr.lock();
		if (target == nullptr) return;

		const std::shared_ptr<Entity> parent = target->_parentPtr.lock();
		if (parent == nullptr) return;

		VectorExtensions::Remove(parent->_childEntities, target);
		target->_parentPtr.reset();

		_rootEntities.push_back(target);

		if (const auto targetTransform = target->GetTransform().lock())
		{
			if (worldPositionStays)
			{
				targetTransform->SetLocalPositionAsWorldPosition();
			}

			targetTransform->RecalculateChildrenHierarchyWorldMatrices();
		}

		if (const auto targetTransform = target->GetUiTransform().lock())
		{
			if (worldPositionStays)
			{
				//targetTransform->SetLocalPositionAsWorldPosition();
			}

			targetTransform->RecalculateChildrenHierarchyWorldUiRects();
		}

		target->RefreshActiveState();
	}

	void EntitiesModule::RefreshUiTransforms()
	{
		for (auto it = _rootEntities.begin(); it != _rootEntities.end(); ++it)
		{
			const std::shared_ptr<Entity> entity = it->lock();
			if (!entity) continue;

			const std::shared_ptr<UiTransformComponent> transform = entity->GetUiTransform().lock();
			if (!transform) continue;

			transform->RecalculateChildrenHierarchyWorldUiRects();
		}
	}

	void EntitiesModule::ForEachEntityInHierarchy(const std::function<void(const std::shared_ptr<Entity> &)> &callback)
	{
		std::vector<std::shared_ptr<Entity>> toCheck;

		for (auto it = _rootEntities.begin(); it != _rootEntities.end(); ++it)
		{
			const std::shared_ptr<Entity> rootEntity = it->lock();
			if (!rootEntity) continue;

			toCheck.push_back(rootEntity);
		}

		while (toCheck.size() > 0)
		{
			std::shared_ptr<Entity> checking = toCheck.front();
			toCheck.erase(toCheck.begin());

			for (auto it = checking->GetChildren().begin(); it != checking->GetChildren().end(); ++it)
			{
				const std::shared_ptr<Entity> childEntity = it->lock();
				if (!childEntity) continue;

				toCheck.push_back(childEntity);
			}

			callback(checking);
		}
	}

	const std::vector<std::weak_ptr<Entity>>& EntitiesModule::GetRootEntities()
	{
		return _rootEntities;
	}

	std::shared_ptr<Entity> EntitiesModule::AddEntity()
	{
		const std::shared_ptr<GEngineCoreApplication> app = _appPtr.lock();
		if (app == nullptr) return std::shared_ptr<Entity>();

		std::shared_ptr<Entity> entity = std::make_shared<Entity>(_appPtr, _nextEntityId);

		entity->SetName(std::format("Entity: {}", _nextEntityId));
		entity->SetActive(true);

		++_nextEntityId;

		_entities.push_back(entity);
		_rootEntities.push_back(entity);

		return entity;
	}

	void EntitiesModule::TickEntities()
	{
		const std::shared_ptr<GEngineCoreApplication> app = _appPtr.lock();
		if (app == nullptr) return;

		ForEachEntityInHierarchy([](const std::shared_ptr<Entity>& entity)
		{
			if (!entity->IsActiveInHierarchy())
			{
				return false;
			}

			entity->TickAllComponents();
			return true;
		});
	}

	void EntitiesModule::ActuallyRemoveEntities()
	{
		for (auto it = _entitiesToRemove.begin(); it != _entitiesToRemove.end(); ++it)
		{
			RemoveEntityNow(*it);
		}

		_entitiesToRemove.clear();
	}
}
