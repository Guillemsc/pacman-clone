//
// Created by guillem on 7/27/25.
//

#ifndef GAMEPLAYENTITIES_H
#define GAMEPLAYENTITIES_H

#include <memory>
#include <vector>

namespace GEngine
{
	class Entity;
}

namespace PacMan
{
	class GameplayEntities
	{
		std::weak_ptr<GEngine::Entity> Player;
		std::vector<std::weak_ptr<GEngine::Entity>> Ghosts;
		std::vector<std::weak_ptr<GEngine::Entity>> Collectables;
	};
}

#endif //GAMEPLAYENTITIES_H
