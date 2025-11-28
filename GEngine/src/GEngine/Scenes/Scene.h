//
// Created by guillem on 8/7/25.
//

#ifndef SCENE_H
#define SCENE_H
#include <memory>

namespace GEngine
{
	class Entity;
	class EntitiesModule;

	class Scene
	{
	public:
		Scene(EntitiesModule* entitiesPtr, const std::string& name);

		void Dispose() const;

		std::weak_ptr<Entity> AddWorldEntity() const;
		std::weak_ptr<Entity> AddUiEntity() const;

	private:
		EntitiesModule* const _entitiesPtr;

		std::weak_ptr<Entity> _rootUiEntity;
		std::weak_ptr<Entity> _rootWorldEntity;
	};
}

#endif //SCENE_H
