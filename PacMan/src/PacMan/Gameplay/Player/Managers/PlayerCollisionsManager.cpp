//
// Created by guillem on 12/4/25.
//

#include "PlayerCollisionsManager.h"

#include "GEngine/Colliders2d/Contact2dData.h"
#include "GEngine/Entities/Entity.h"
#include "PacMan/Gameplay/Entities/Components/EntityIdComponent.h"
#include "PacMan/Gameplay/Entities/Enums/EntityType.h"
#include "spdlog/spdlog.h"

namespace PacMan
{
	void PlayerCollisionsManager::WhenPlayerCollided(const GEngine::Contact2dData &contact)
	{
		const std::shared_ptr<GEngine::Entity> collider = contact.collider.lock();
		if (!collider) return;

		const std::shared_ptr<EntityIdComponent> entityId = collider->GetComponent<EntityIdComponent>().lock();
		if (!entityId) return;

		switch (entityId->GetType())
		{
			case EntityType::PELLET:
			{
				collider->SetActive(false);
			}
		}
	}
}
