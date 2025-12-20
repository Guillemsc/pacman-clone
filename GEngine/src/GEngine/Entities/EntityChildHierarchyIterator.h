//
// Created by guillem on 12/20/25.
//

#ifndef ENTITYTREEITERATOR_H
#define ENTITYTREEITERATOR_H

#include <memory>
#include <vector>

#include "GEngine/Pooling/ObjectPool.h"

namespace GEngine
{
	class Entity;
}

namespace GEngine
{
	class EntityChildHierarchyIterator
	{
	public:
		explicit EntityChildHierarchyIterator(const std::weak_ptr<Entity> &entity);

		bool HasNext() const;
		[[nodiscard]] Entity* GetNext(bool automaticallyAddChildren = true);
		void AddCurrentChildren();

	private:
		std::weak_ptr<Entity> _currentEntity;
		std::weak_ptr<Entity> _entityToAddChildren;

		ObjectPool<std::vector<std::shared_ptr<Entity>>>::Ptr _pooledVector;
	};
}

#endif //ENTITYTREEITERATOR_H
