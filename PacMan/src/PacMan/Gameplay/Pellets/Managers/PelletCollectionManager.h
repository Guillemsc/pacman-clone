//
// Created by guillem on 12/11/25.
//

#ifndef PELLETCOLLECTIONMANAGER_H
#define PELLETCOLLECTIONMANAGER_H

#include <memory>

namespace PacMan
{
	class GhostsBehaviourManager;
}

namespace GEngine
{
	class Entity;
}

namespace PacMan
{
	class PelletCollectionManager
	{
	public:
		explicit PelletCollectionManager(
			GhostsBehaviourManager* ghostsBehaviourManager
			);

		void HandlePelletCollected(const std::shared_ptr<GEngine::Entity>& pelletEntity);
		void HandleBigPelletCollected(const std::shared_ptr<GEngine::Entity>& pelletEntity);

	private:
		GhostsBehaviourManager* const _ghostsBehaviourManager;
	};
}

#endif //PELLETCOLLECTIONMANAGER_H
