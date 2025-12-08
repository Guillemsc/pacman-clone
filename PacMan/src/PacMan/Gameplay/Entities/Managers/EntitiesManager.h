//
// Created by guillem on 12/5/25.
//

#ifndef ENTITIESMANAGER_H
#define ENTITIESMANAGER_H
#include <memory>

namespace GEngine
{
	class Entity;
}

namespace PacMan
{
	class GameplayEntities;

	class EntitiesManager
	{
	public:
		explicit EntitiesManager(GameplayEntities* entities);

		void StopAllEntitiesMovement();
		void StartPlayerAndMapGhostEntitiesMovement();

	private:
		void SetEntityMovementEnabled(const std::weak_ptr<GEngine::Entity>& entity, bool set);

	private:
		GameplayEntities* const _entities;
	};
}

#endif //ENTITIESMANAGER_H
