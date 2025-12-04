//
// Created by guillem on 12/4/25.
//

#ifndef PLAYERCOLLISIONSMANAGER_H
#define PLAYERCOLLISIONSMANAGER_H

namespace GEngine
{
	struct Contact2dData;
}

namespace PacMan
{
	class PlayerCollisionsManager
	{
	public:

		void WhenPlayerCollided(const GEngine::Contact2dData& contact);
	};
}

#endif //PLAYERCOLLISIONSMANAGER_H
