//
// Created by guillem on 11/27/25.
//

#ifndef GHOSTSLOADERMANAGER_H
#define GHOSTSLOADERMANAGER_H

#include <memory>
#include <string>

#include "GEngine/Colors/Color01.h"
#include "glm/fwd.hpp"
#include "PacMan/Gameplay/Ghosts/Data/LoadedGhostsData.h"
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
	class MapMovementManager;
	struct LoadedMapData;

	class GhostsLoadingManager
	{
	public:
		explicit GhostsLoadingManager(
			GEngine::GEngineCoreModules* modules,
			GEngine::Scene* scene,
			MapMovementManager* mapMovementManager,
			GameplayEntities* gameplayEntities
			);

		void LoadGhosts(const LoadedMapData& loadedMapData);
		const LoadedGhostsData& GetLoadedGhostsData() const;

	private:
		std::shared_ptr<GEngine::Entity> LoadGhost(GhostType ghostType, const glm::i32vec2& gridPosition, bool isPrision);

		std::string GetGhostName(GhostType ghostType);
		GEngine::Color01 GetGhostColor(GhostType ghostType);
		void SetupGhostAi(GEngine::Entity* ghostEntity, GhostType ghostType);

	private:
		GEngine::GEngineCoreModules* const _modules;
		GEngine::Scene* const _scene;
		MapMovementManager* const _mapMovementManager;
		GameplayEntities* const _gameplayEntities;

		LoadedGhostsData _loadedGhostsData;
	};
}

#endif //GHOSTSLOADERMANAGER_H
