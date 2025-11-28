//
// Created by guillem on 11/27/25.
//

#ifndef GHOSTSLOADERMANAGER_H
#define GHOSTSLOADERMANAGER_H

#include <memory>
#include <string>

#include "GEngine/Colors/Color01.h"
#include "glm/fwd.hpp"
#include "PacMan/Gameplay/Ghosts/Enums/GhostType.h"

namespace GEngine
{
	class Entity;
	class Scene;
	class GEngineCoreModules;
}

namespace PacMan
{
	class GameplayEntities;
	class MapMovementSystem;
	class MapMovementManager;
	struct LoadedMapData;

	class GhostsLoaderManager
	{
	public:
		explicit GhostsLoaderManager(
			GEngine::GEngineCoreModules* modules,
			GEngine::Scene* scene,
			MapMovementManager* mapMovementManager,
			MapMovementSystem* mapMovementSystem,
			GameplayEntities* gameplayEntities
			);

		void LoadGhosts(const LoadedMapData& loadedMapData);

	private:
		void LoadGhost(GhostType ghostType, const glm::i32vec2& gridPosition, bool isPrision);

		std::string GetGhostName(GhostType ghostType);
		GEngine::Color01 GetGhostColor(GhostType ghostType);

	private:
		GEngine::GEngineCoreModules* const _modules;
		GEngine::Scene* const _scene;
		MapMovementManager* const _mapMovementManager;
		MapMovementSystem* const _mapMovementSystem;
		GameplayEntities* const _gameplayEntities;
	};
}

#endif //GHOSTSLOADERMANAGER_H
