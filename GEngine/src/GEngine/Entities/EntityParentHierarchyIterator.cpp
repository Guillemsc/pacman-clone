//
// Created by guillem on 12/20/25.
//

#include "EntityParentHierarchyIterator.h"

#include "Entity.h"

namespace GEngine
{
	EntityParentHierarchyIterator::EntityParentHierarchyIterator(const std::weak_ptr<Entity> &entity)
	{
		_currentEntity = entity;
	}

	bool EntityParentHierarchyIterator::HasNext() const
	{
		return !_currentEntity.expired();
	}

	Entity* EntityParentHierarchyIterator::GetNext()
	{
		const std::shared_ptr<Entity> currentEntity = _currentEntity.lock();
		if (!currentEntity) return nullptr;

		_currentEntity = currentEntity->GetParent();

		return currentEntity.get();
	}
}
