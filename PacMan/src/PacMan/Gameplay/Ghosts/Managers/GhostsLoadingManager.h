//
// Created by guillem on 11/27/25.
//

#ifndef GHOSTSLOADERMANAGER_H
#define GHOSTSLOADERMANAGER_H

#include <memory>
#include <string>

#include "GEngine/Colors/Color01.h"
#include "glm/vec2.hpp"
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
	class MapMovementComponent;
	struct GhostsStateData;
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
			GameplayEntities* gameplayEntities,
			GhostsStateData* ghostsStateData
			);

		void LoadGhosts(const LoadedMapData& loadedMapData);
		[[nodiscard]] const LoadedGhostsData& GetLoadedGhostsData() const;

		void SetGhostsToInitialPosition();

	private:
		std::shared_ptr<GEngine::Entity> LoadGhost(GhostType ghostType, const glm::i32vec2& gridPosition, bool isPrision);

		void SetGhostToInitialPosition(
			const std::weak_ptr<GEngine::Entity>& entity,
			const glm::i32vec2& gridPosition,
			bool isPrision
			) const;

		std::string GetGhostName(GhostType ghostType);
		GEngine::Color01 GetGhostColor(GhostType ghostType);
		void SetupGhostAi(
			GEngine::Entity* ghostEntity,
			const std::weak_ptr<MapMovementComponent>& mapMovement,
			GhostType ghostType
			) const;

	private:
		GEngine::GEngineCoreModules* const _modules;
		GEngine::Scene* const _scene;
		MapMovementManager* const _mapMovementManager;
		GameplayEntities* const _gameplayEntities;
		GhostsStateData* const _ghostsStateData;

		glm::i32vec2 _mapGhostInitialGridPosition = glm::i32vec2(0);
		glm::i32vec2 _ghostPrisionLeftSlotInitialGridPosition = glm::i32vec2(0);
		glm::i32vec2 _ghostPrisionCenterSlotInitialGridPosition = glm::i32vec2(0);
		glm::i32vec2 _ghostPrisionRightSlotInitialGridPosition = glm::i32vec2(0);


		LoadedGhostsData _loadedGhostsData;
	};
}

#endif //GHOSTSLOADERMANAGER_H
