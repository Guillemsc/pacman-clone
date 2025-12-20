//
// Created by guillem on 12/20/25.
//

#ifndef ENTITYPARENTHIERARCHYITERATOR_H
#define ENTITYPARENTHIERARCHYITERATOR_H

#include <memory>

namespace GEngine
{
	class Entity;

	class EntityParentHierarchyIterator
	{
	public:
		explicit EntityParentHierarchyIterator(const std::weak_ptr<Entity> &entity);

		bool HasNext() const;
		[[nodiscard]] Entity* GetNext();

	private:
		std::weak_ptr<Entity> _currentEntity;
	};
}

#endif //ENTITYPARENTHIERARCHYITERATOR_H
