//
// Created by guillem on 12/5/25.
//

#include "EntitiesManager.h"

#include <memory>

#include "GEngine/Entities/Entity.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"

namespace PacMan
{
	EntitiesManager::EntitiesManager(GameplayEntities *entities)
		: _entities(entities)
	{
	}

	void EntitiesManager::StopAllEntitiesMovement()
	{
		StopEntityMovement(_entities->Player);

		for (const std::weak_ptr<GEngine::Entity>& ghost : _entities->Ghosts)
		{
			StopEntityMovement(ghost);
		}

		for (const std::weak_ptr<GEngine::Entity>& ghost : _entities->Collectables)
		{
			StopEntityMovement(ghost);
		}
	}

	void EntitiesManager::StopEntityMovement(const std::weak_ptr<GEngine::Entity>& entity)
	{
		const std::shared_ptr<GEngine::Entity> lEntity = entity.lock();
		if (!lEntity) return;

		const std::shared_ptr<MapMovementComponent>& mapMovement = lEntity->GetComponent<MapMovementComponent>().lock();
		if (!mapMovement) return;

		mapMovement->SetCanMove(false);
	}
}
