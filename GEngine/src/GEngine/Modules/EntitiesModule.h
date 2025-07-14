//
// Created by guillem on 6/6/25.
//

#ifndef ENTITIESMODULE_H
#define ENTITIESMODULE_H

#include <functional>
#include <memory>
#include <vector>

namespace GEngine
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

		std::weak_ptr<Entity> AddWorldEntity();
		std::weak_ptr<Entity> AddUiEntity();
		bool RemoveEntity(const std::weak_ptr<Entity> &entityPtr);
		bool RemoveEntityNow(const std::weak_ptr<Entity> &entityPtr);
		void RemoveAllEntitiesNow();

		void SetEntityParent(const std::weak_ptr<Entity> &targetPtr, const std::weak_ptr<Entity> &parentPtr, bool worldPositionStays = true);
		void RemoveEntityParent(const std::weak_ptr<Entity>& targetPtr, bool worldPositionStays = true);

		void RefreshUiTransforms();

		void ForEachEntityInHierarchy(const std::function<void(const std::shared_ptr<Entity>&)> &callback);

		const std::vector<std::weak_ptr<Entity>>& GetRootEntities();

	private:
		std::shared_ptr<Entity> AddEntity();
		void TickEntities();
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
