//
// Created by guillem on 12/4/25.
//

#ifndef PLAYERCOLLISIONSMANAGER_H
#define PLAYERCOLLISIONSMANAGER_H

#include <memory>

namespace PacMan
{
	class GhostsPrisionManager;
	class GhostsBehaviourManager;
}

namespace PacMan
{
	struct GhostsStateData;
	class PelletCollectionManager;
	class PlayerDeathManager;
}

namespace GEngine
{
	class Entity;
	struct Contact2dData;
}

namespace PacMan
{
	class PlayerCollisionsManager
	{
	public:
		explicit PlayerCollisionsManager(
			PelletCollectionManager* pelletCollectionManager,
			GhostsPrisionManager* ghostsPrisionManager,
			GhostsStateData* ghostsStateData
		);
		void Init(PlayerDeathManager* playerDeathManager);

		void WhenPlayerCollided(const GEngine::Contact2dData& contact) const;

	private:
		void HandleGhostCollision(const std::shared_ptr<GEngine::Entity>& collider) const;

	private:
		PelletCollectionManager* const _pelletCollectionManager;
		GhostsPrisionManager* const _ghostsPrisionManager;
		GhostsStateData* const _ghostsStateData;

		PlayerDeathManager* _playerDeathManager = nullptr;
	};
}

#endif //PLAYERCOLLISIONSMANAGER_H
