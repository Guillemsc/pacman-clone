//
// Created by guillem on 11/27/25.
//

#include "GhostsLoaderManager.h"

#include "GEngine/Components/Shape2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Scenes/Scene.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"
#include "PacMan/Gameplay/Ghosts/Components/RedGhostAiComponent.h"
#include "PacMan/Gameplay/MapLoading/Data/LoadedMapData.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"

namespace PacMan
{
	GhostsLoaderManager::GhostsLoaderManager(
		GEngine::GEngineCoreModules *modules,
		GEngine::Scene *scene,
		MapMovementManager *mapMovementManager,
		GameplayEntities *gameplayEntities
		): _modules(modules),
		_scene(scene),
		_mapMovementManager(mapMovementManager),
		_gameplayEntities(gameplayEntities)
	{
	}

	void GhostsLoaderManager::LoadGhosts(const LoadedMapData &loadedMapData)
	{
		LoadGhost(RED_GHOST_TYPE, loadedMapData.RedGhostPosition, false);
		_loadedGhostsData.LeftPrisionSlotGhostEntity = LoadGhost(CIAN_GHOST_TYPE, loadedMapData.GhostPrisionLeftSlotPosition, true);
		_loadedGhostsData.CenterPrisionSlotGhostEntity = LoadGhost(PINK_GHOST_TYPE, loadedMapData.GhostPrisionCenterSlotPosition, true);
		_loadedGhostsData.RightPrisionSlotGhostEntity = LoadGhost(ORANGE_GHOST_TYPE, loadedMapData.GhostPrisionRightSlotPosition, true);
	}

	const LoadedGhostsData & GhostsLoaderManager::GetLoadedGhostsData() const
	{
		return _loadedGhostsData;
	}

	std::shared_ptr<GEngine::Entity> GhostsLoaderManager::LoadGhost(const GhostType ghostType, const glm::i32vec2 &gridPosition, const bool isPrision)
	{
		const std::string ghostName = GetGhostName(ghostType);
		const GEngine::Color01 ghostColor = GetGhostColor(ghostType);

		const std::shared_ptr<GEngine::Entity> ghostEntity = _scene->AddWorldEntity().lock();
		ghostEntity->SetName("Player" + ghostName);

		const std::shared_ptr<GEngine::Shape2dRendererComponent> shape = ghostEntity->AddComponent<GEngine::Shape2dRendererComponent>().lock();
		shape->SetLayer(1);
		shape->SetColor(ghostColor);

		if (isPrision)
		{
			const glm::vec2 worldPosition = _mapMovementManager->GridPositionToWorldPosition(gridPosition, GEngine::CellPosition::CENTER_RIGHT);
			ghostEntity->GetTransform().lock()->SetPositionXY(worldPosition);
		}
		else
		{
			const std::shared_ptr<MapMovementComponent> mapMovement = ghostEntity->AddComponent<MapMovementComponent>().lock();
			mapMovement->SetGridPosition(gridPosition);

			SetupGhostAi(ghostEntity.get(), ghostType);

			const std::shared_ptr<GhostAiComponent> ai = ghostEntity->GetComponent<GhostAiComponent>().lock();
			ai->Init(mapMovement);
		}

		_gameplayEntities->Ghosts.push_back(ghostEntity);

		return ghostEntity;
	}

	std::string GhostsLoaderManager::GetGhostName(const GhostType ghostType)
	{
		switch (ghostType)
		{
			case RED_GHOST_TYPE:
				return "Red";
			case ORANGE_GHOST_TYPE:
				return "Orange";
			case CIAN_GHOST_TYPE:
				return "Cian";
			case PINK_GHOST_TYPE:
				return "Pink";
		}

		return "Unknown";
	}

	GEngine::Color01 GhostsLoaderManager::GetGhostColor(const GhostType ghostType)
	{
		switch (ghostType)
		{
			case RED_GHOST_TYPE:
				return GEngine::Color01(1, 0, 0);
			case ORANGE_GHOST_TYPE:
				return GEngine::Color01(1, 0.3f, 0);
			case CIAN_GHOST_TYPE:
				return GEngine::Color01(0, 0.9f, 0.9f);
			case PINK_GHOST_TYPE:
				return GEngine::Color01(0.8, 0.3f, 0.7f);
		}

		return GEngine::Color01(0, 0, 0);;
	}

	void GhostsLoaderManager::SetupGhostAi(GEngine::Entity *ghostEntity, const GhostType ghostType)
	{
		switch (ghostType)
		{
			case RED_GHOST_TYPE:
			{
				ghostEntity->AddComponent<RedGhostAiComponent>();
				break;
			}
			case ORANGE_GHOST_TYPE:
			{
				break;
			}
			case CIAN_GHOST_TYPE:
			{
				break;
			}
			case PINK_GHOST_TYPE:
			{
				break;
			}
		}
	}
}
