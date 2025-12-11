//
// Created by guillem on 12/4/25.
//

#include "PlayerCollisionsManager.h"

#include "PlayerDeathManager.h"
#include "GEngine/Colliders2d/Contact2dData.h"
#include "GEngine/Entities/Entity.h"
#include "PacMan/Gameplay/Entities/Components/EntityIdComponent.h"
#include "PacMan/Gameplay/Entities/Enums/EntityType.h"
#include "PacMan/Gameplay/Pellets/Managers/PelletCollectionManager.h"
#include "spdlog/spdlog.h"

namespace PacMan
{
	PlayerCollisionsManager::PlayerCollisionsManager(PelletCollectionManager *pelletCollectionManager)
		: _pelletCollectionManager(pelletCollectionManager)
	{

	}

	void PlayerCollisionsManager::Init(PlayerDeathManager *playerDeathManager)
	{
		_playerDeathManager = playerDeathManager;
	}

	void PlayerCollisionsManager::WhenPlayerCollided(const GEngine::Contact2dData &contact) const
	{
		const std::shared_ptr<GEngine::Entity> collider = contact.collider.lock();
		if (!collider) return;

		const std::shared_ptr<EntityIdComponent> entityId = collider->GetComponent<EntityIdComponent>().lock();
		if (!entityId) return;

		switch (entityId->GetType())
		{
			case EntityType::PELLET:
			{
				_pelletCollectionManager->HandlePelletCollected(collider);
				break;
			}

			case EntityType::BIG_PELLET:
			{
				_pelletCollectionManager->HandleBigPelletCollected(collider);
				break;
			}

			case EntityType::GHOST:
			{
				HandleGhostCollision(collider);
				break;
			}
		}
	}

	void PlayerCollisionsManager::HandleGhostCollision(const std::shared_ptr<GEngine::Entity> &collider) const
	{
		_playerDeathManager->RunDeath();
	}
}
