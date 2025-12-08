//
// Created by guillem on 12/5/25.
//

#include "EntitiesManager.h"

#include <memory>

#include "GEngine/Entities/Entity.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"
#include "PacMan/Gameplay/Ghosts/Components/RedGhostAiComponent.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"

namespace PacMan
{
	EntitiesManager::EntitiesManager(GameplayEntities *entities)
		: _entities(entities)
	{
	}

	void EntitiesManager::StopAllEntitiesMovement()
	{
		SetEntityMovementEnabled(_entities->Player, false);

		for (const std::weak_ptr<GEngine::Entity>& ghost : _entities->Ghosts)
		{
			SetEntityMovementEnabled(ghost, false);
		}

		for (const std::weak_ptr<GEngine::Entity>& collectables : _entities->Collectables)
		{
			SetEntityMovementEnabled(collectables, false);
		}
	}

	void EntitiesManager::StartPlayerAndMapGhostEntitiesMovement()
	{
		SetEntityMovementEnabled(_entities->Player, true);

		for (const std::weak_ptr<GEngine::Entity>& ghost : _entities->Ghosts)
		{
			const std::shared_ptr<GEngine::Entity> lEntity = ghost.lock();
			if (!lEntity) continue;

			const bool isRedGhost = lEntity->HasComponent<RedGhostAiComponent>();
			if (!isRedGhost) continue;

			const std::shared_ptr<MapMovementComponent>& mapMovement = lEntity->GetComponent<MapMovementComponent>().lock();
			if (!mapMovement) continue;

			mapMovement->SetCanMove(true);
		}
	}

	void EntitiesManager::SetEntityMovementEnabled(const std::weak_ptr<GEngine::Entity>& entity, const bool set)
	{
		const std::shared_ptr<GEngine::Entity> lEntity = entity.lock();
		if (!lEntity) return;

		const std::shared_ptr<MapMovementComponent>& mapMovement = lEntity->GetComponent<MapMovementComponent>().lock();
		if (!mapMovement) return;

		mapMovement->SetCanMove(set);
	}
}
