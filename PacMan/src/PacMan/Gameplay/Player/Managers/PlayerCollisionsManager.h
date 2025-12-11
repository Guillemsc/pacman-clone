//
// Created by guillem on 12/4/25.
//

#ifndef PLAYERCOLLISIONSMANAGER_H
#define PLAYERCOLLISIONSMANAGER_H

#include <memory>

namespace PacMan
{
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
			PelletCollectionManager* pelletCollectionManager
		);
		void Init(PlayerDeathManager* playerDeathManager);

		void WhenPlayerCollided(const GEngine::Contact2dData& contact) const;

	private:
		void HandleGhostCollision(const std::shared_ptr<GEngine::Entity>& collider) const;

	private:
		PelletCollectionManager* const _pelletCollectionManager;

		PlayerDeathManager* _playerDeathManager = nullptr;
	};
}

#endif //PLAYERCOLLISIONSMANAGER_H
