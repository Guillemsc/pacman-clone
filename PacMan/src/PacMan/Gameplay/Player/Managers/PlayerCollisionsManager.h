//
// Created by guillem on 12/4/25.
//

#ifndef PLAYERCOLLISIONSMANAGER_H
#define PLAYERCOLLISIONSMANAGER_H
#include <memory>

namespace PacMan
{
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
		explicit PlayerCollisionsManager();
		void Init(PlayerDeathManager* playerDeathManager);

		void WhenPlayerCollided(const GEngine::Contact2dData& contact) const;

	private:
		void HandleGhostCollision(const std::shared_ptr<GEngine::Entity>& collider) const;

	private:
		PlayerDeathManager* _playerDeathManager = nullptr;
	};
}

#endif //PLAYERCOLLISIONSMANAGER_H
