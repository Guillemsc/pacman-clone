//
// Created by guillem on 6/6/25.
//

#include "EntitiesModule.h"

#include <format>

#include "GEngine/Entities/Entity.h"
#include "GEngine/Extensions/VectorExtensions.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Components/UiTransformComponent.h"
#include "GEngine/Pooling/Pools.h"
#include "spdlog/spdlog.h"

namespace GEngine
{
	EntitiesModule::EntitiesModule()
	{

	}

	void EntitiesModule::Init(GEngineCoreModules* modules)
	{
		_modules = modules;
	}

	void EntitiesModule::Tick()
	{
		TickEntities();
	}

	void EntitiesModule::LateTick()
	{
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

	std::weak_ptr<Entity> EntitiesModule::AddWorldEntity(const std::weak_ptr<Entity> &parent)
	{
		const std::shared_ptr<Entity> entity = AddWorldEntity().lock();
		if (!entity) return std::weak_ptr<Entity>();

		entity->SetParent(parent);

		return entity;
	}

	std::weak_ptr<Entity> EntitiesModule::AddUiEntity()
	{
		std::shared_ptr<Entity> entity = AddEntity();
		if (!entity) return std::weak_ptr<Entity>();

		entity->AddComponent<UiTransformComponent>();

		return entity;
	}

	std::weak_ptr<Entity> EntitiesModule::AddUiEntity(const std::weak_ptr<Entity> &parent)
	{
		const std::shared_ptr<Entity> entity = AddUiEntity().lock();
		if (!entity) return std::weak_ptr<Entity>();

		entity->SetParent(parent);

		return entity;
	}

	bool EntitiesModule::RemoveEntity(const std::weak_ptr<Entity> &entityPtr)
	{
		const std::shared_ptr<Entity> entity = entityPtr.lock();
		if (!entity) return false;

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
		const std::shared_ptr<Entity> entity = entityPtr.lock();
		if (!entity) return false;

		if (!entity->_parent.expired())
		{
			entity->RemoveParent();
		}

		VectorExtensions::Remove(_rootEntities, entity);

		const ObjectPool<std::vector<std::shared_ptr<Entity>>>::Ptr entitiesBuffer = Pools::entitiesVector.Acquire();

		entitiesBuffer->push_back(entity);

		while (entitiesBuffer->size() > 0)
		{
			const std::shared_ptr<Entity> checking = entitiesBuffer->front();
			entitiesBuffer->erase(entitiesBuffer->begin());

			for (auto it = checking->_childEntities.begin(); it != checking->_childEntities.end(); ++it)
			{
				const std::shared_ptr<Entity> child = it->lock();
				if (child == nullptr) continue;

				entitiesBuffer->push_back(child);
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
		const std::shared_ptr<Entity> target = targetPtr.lock();
		if (!target) return;

		const std::shared_ptr<Entity> parent = parentPtr.lock();
		if (!parent) return;

		const bool isInsideChildHierarchy = parent->IsInsideChildHierarchy(target);
		if (isInsideChildHierarchy) return;

		if (!target->_parent.expired())
		{
			RemoveEntityParent(target);
		}

		target->_parent = parent;
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
		const std::shared_ptr<Entity> target = targetPtr.lock();
		if (target == nullptr) return;

		const std::shared_ptr<Entity> parent = target->_parent.lock();
		if (parent == nullptr) return;

		VectorExtensions::Remove(parent->_childEntities, target);
		target->_parent.reset();

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
		const ObjectPool<std::vector<std::shared_ptr<Entity>>>::Ptr entitiesBuffer = Pools::entitiesVector.Acquire();

		for (auto it = _rootEntities.begin(); it != _rootEntities.end(); ++it)
		{
			const std::shared_ptr<Entity> rootEntity = it->lock();
			if (!rootEntity) continue;

			entitiesBuffer->push_back(rootEntity);
		}

		while (entitiesBuffer->size() > 0)
		{
			std::shared_ptr<Entity> checking = entitiesBuffer->front();
			entitiesBuffer->erase(entitiesBuffer->begin());

			for (auto it = checking->GetChildren().begin(); it != checking->GetChildren().end(); ++it)
			{
				const std::shared_ptr<Entity> childEntity = it->lock();
				if (!childEntity) continue;

				entitiesBuffer->push_back(childEntity);
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
		std::shared_ptr<Entity> entity = std::make_shared<Entity>(_modules, _nextEntityId);

		entity->SetName(std::format("Entity: {}", _nextEntityId));
		entity->SetActive(true);

		++_nextEntityId;

		_entities.push_back(entity);
		_rootEntities.push_back(entity);

		return entity;
	}

	void EntitiesModule::TickEntities()
	{
		_tickEntitiesBuffer.clear();

		for (auto it = _rootEntities.begin(); it != _rootEntities.end(); ++it)
		{
			const std::shared_ptr<Entity> rootEntity = it->lock();
			if (!rootEntity) continue;

			_tickEntitiesBuffer.push_back(rootEntity.get());
		}

		std::int32_t entityIndex = 0;
		while (_tickEntitiesBuffer.size() > 0)
		{
			Entity* checking = _tickEntitiesBuffer.front();
			_tickEntitiesBuffer.pop_front();

			if (!checking->IsActiveInHierarchy()) continue;

			for (auto it = checking->GetChildren().rbegin(); it != checking->GetChildren().rend(); ++it)
			{
				const std::shared_ptr<Entity> childEntity = it->lock();
				if (!childEntity) continue;

				_tickEntitiesBuffer.push_front(childEntity.get());
			}

			checking->_renderingPositionInHierarchy = entityIndex;
			checking->TickAllComponents();

			++entityIndex;
		}
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
