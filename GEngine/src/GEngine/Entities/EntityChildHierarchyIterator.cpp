//
// Created by guillem on 12/20/25.
//

#include "EntityChildHierarchyIterator.h"

#include "GEngine/Pooling/Pools.h"

namespace GEngine
{
	EntityChildHierarchyIterator::EntityChildHierarchyIterator(const std::weak_ptr<Entity> &entity)
	{
		_currentEntity = entity;
		_pooledVector = Pools::entitiesVector.Acquire();
		_pooledVector->push_back(_currentEntity.lock());
	}

	bool EntityChildHierarchyIterator::HasNext() const
	{
		return !_pooledVector->empty();
	}

	Entity* EntityChildHierarchyIterator::GetNext(const bool automaticallyAddChildren)
	{
		_entityToAddChildren.reset();

		if (_pooledVector->empty()) return nullptr;

		const std::shared_ptr<Entity>& entity = _pooledVector->front();
		_pooledVector->erase(_pooledVector->begin());

		if (!entity) return nullptr;

		if (automaticallyAddChildren)
		{
			const std::vector<std::weak_ptr<Entity>>& children = entity->GetChildren();
			for (auto it = children.begin(); it != children.end(); ++it)
			{
				const std::shared_ptr<Entity> childEntity = it->lock();
				if (!childEntity) continue;

				_pooledVector->push_back(childEntity);
			}
		}
		else
		{
			_entityToAddChildren = entity;
		}

		return entity.get();
	}

	void EntityChildHierarchyIterator::AddCurrentChildren()
	{
		const std::shared_ptr<Entity>& entity = _entityToAddChildren.lock();
		if (!entity) return;

		for (auto it = entity->GetChildren().begin(); it != entity->GetChildren().end(); ++it)
		{
			const std::shared_ptr<Entity> childEntity = it->lock();
			if (!childEntity) continue;

			_pooledVector->push_back(childEntity);
		}

		_entityToAddChildren.reset();
	}
}
