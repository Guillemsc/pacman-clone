//
// Created by guillem on 6/6/25.
//

#ifndef ENTITIESMODULE_H
#define ENTITIESMODULE_H

#include <functional>
#include <memory>
#include <vector>

namespace GEngineCore
{
	class GEngineCoreApplication;
	class ComponentsModule;
	struct EntityRef;
	class Entity;

	class EntitiesModule
	{
		friend class Entity;

	public:
		EntitiesModule();

		void Init(const std::weak_ptr<GEngineCoreApplication>& app);
		void Tick();
		void Dispose();

		std::weak_ptr<Entity> AddEntity();
		bool RemoveEntity(const std::weak_ptr<Entity> &entityPtr);
		bool RemoveEntityNow(const std::weak_ptr<Entity> &entityPtr);
		void RemoveAllEntities();

		void SetEntityParent(const std::weak_ptr<Entity> &targetPtr, const std::weak_ptr<Entity> &parentPtr, bool worldPositionStays = true);
		void RemoveEntityParent(const std::weak_ptr<Entity>& targetPtr, bool worldPositionStays = true);

		void ForEachEntityInHierarchy(const std::function<void(const std::shared_ptr<Entity>&)> &callback);

		void TickEntities();

		const std::vector<std::weak_ptr<Entity>>& GetRootEntities();

	private:
		void ActuallyRemoveEntities();

	private:
		std::weak_ptr<GEngineCoreApplication> _appPtr;

		std::vector<std::shared_ptr<Entity>> _entities;
		std::vector<std::weak_ptr<Entity>> _rootEntities;
		std::vector<std::weak_ptr<Entity>> _entitiesToRemove;
		std::uint32_t _nextEntityId = 1;

		std::vector<std::shared_ptr<Entity>> _checkingRemovingEntitiesBuffer;
	};
}

#endif //ENTITIESMODULE_H
