//
// Created by guillem on 6/6/25.
//

#include "EntitiesModule.h"

#include <format>

#include "Entities/Entity.h"
#include "Extensions/VectorExtensions.h"
#include "Components/TransformComponent.h"
#include "Modules/ComponentsModule.h"

namespace GEngineCore
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
		RemoveAllEntities();
	}

	std::weak_ptr<Entity> EntitiesModule::AddEntity()
	{
		const std::shared_ptr<GEngineCoreApplication> app = _appPtr.lock();
		if (app == nullptr) return std::weak_ptr<Entity>();

		const std::shared_ptr<ComponentsModule> components = app->Components().lock();
		if (components == nullptr) return std::weak_ptr<Entity>();

		std::shared_ptr<Entity> entity = std::make_shared<Entity>(_appPtr, _nextEntityId);

		entity->SetName(std::format("Entity: {}", _nextEntityId));
		entity->SetActive(true);

		entity->_transformPtr = components->AddEntityComponent<TransformComponent>(entity);

		++_nextEntityId;

		_entities.push_back(entity);
		_rootEntities.push_back(entity);

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

		const std::shared_ptr<ComponentsModule> components = app->Components().lock();
		if (components == nullptr) return false;

		const std::shared_ptr<Entity> entity = entityPtr.lock();
		if (entity == nullptr) return false;

		entity->RemoveParent();

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

			components->RemoveAllComponentsFromEntity(checking);
			checking->Dispose();

			VectorExtensions::Remove(_entities, checking);
		}

		return true;
	}

	void EntitiesModule::RemoveAllEntities()
	{
		while (_rootEntities.size() > 0)
		{
			std::weak_ptr<Entity> entityPtr = _rootEntities.front();

			if (entityPtr.expired()) return;
			std::shared_ptr<Entity> entity = entityPtr.lock();

			RemoveEntityNow(entity);
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

			targetTransform->RecalculateWorldMatrix();
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

			targetTransform->RecalculateWorldMatrix();
		}

		target->RefreshActiveState();
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

	void EntitiesModule::TickEntities()
	{
		const std::shared_ptr<GEngineCoreApplication> app = _appPtr.lock();
		if (app == nullptr) return;

		const std::shared_ptr<ComponentsModule> components = app->Components().lock();
		if (components == nullptr) return;

		ForEachEntityInHierarchy([components](const std::shared_ptr<Entity>& entity)
		{
			if (!entity->IsActiveInHierarchy())
			{
				return false;
			}

			components->TickEntityComponents(entity.get());
			return true;
		});
	}

	const std::vector<std::weak_ptr<Entity>>& EntitiesModule::GetRootEntities()
	{
		return _rootEntities;
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
