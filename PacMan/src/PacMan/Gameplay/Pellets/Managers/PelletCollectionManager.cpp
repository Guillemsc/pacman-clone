//
// Created by guillem on 12/11/25.
//

#include "PelletCollectionManager.h"

#include "GEngine/Entities/Entity.h"
#include "PacMan/Gameplay/Ghosts/Managers/GhostsBehaviourManager.h"

namespace PacMan
{
	PelletCollectionManager::PelletCollectionManager(GhostsBehaviourManager *ghostsBehaviourManager)
		: _ghostsBehaviourManager(ghostsBehaviourManager)
	{
	}

	void PelletCollectionManager::HandlePelletCollected(const std::shared_ptr<GEngine::Entity> &pelletEntity)
	{
		pelletEntity->SetActive(false);
	}

	void PelletCollectionManager::HandleBigPelletCollected(const std::shared_ptr<GEngine::Entity> &pelletEntity)
	{
		pelletEntity->SetActive(false);
		_ghostsBehaviourManager->SetGhostsFrightened();
	}
}
