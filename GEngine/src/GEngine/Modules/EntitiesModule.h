//
// Created by guillem on 6/6/25.
//

#ifndef ENTITIESMODULE_H
#define ENTITIESMODULE_H

#include <functional>
#include <memory>
#include <vector>

#include "GEngine/Core/GEngineCoreModules.h"

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

		void Init(GEngineCoreModules* modules);
		void Tick();
		void Dispose();

		std::weak_ptr<Entity> AddWorldEntity();
		std::weak_ptr<Entity> AddWorldEntity(const std::weak_ptr<Entity> &parent);
		std::weak_ptr<Entity> AddUiEntity();
		std::weak_ptr<Entity> AddUiEntity(const std::weak_ptr<Entity> &parent);
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
		GEngineCoreModules* _modules = nullptr;

		std::vector<std::shared_ptr<Entity>> _entities;
		std::vector<std::weak_ptr<Entity>> _rootEntities;
		std::vector<std::weak_ptr<Entity>> _entitiesToRemove;
		std::uint32_t _nextEntityId = 1;

		std::vector<std::shared_ptr<Entity>> _checkingRemovingEntitiesBuffer;
	};
}

#endif //ENTITIESMODULE_H
