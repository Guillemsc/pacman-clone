//
// Created by guillem on 11/27/25.
//

#include "GhostsLoadingManager.h"

#include "GEngine/Components/Collider2dComponent.h"
#include "GEngine/Components/Shape2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Logging/GEngineLog.h"
#include "GEngine/Scenes/Scene.h"
#include "PacMan/Gameplay/Collisions/Enums/CollisionLayers.h"
#include "PacMan/Gameplay/Entities/Components/EntityIdComponent.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"
#include "PacMan/Gameplay/Ghosts/Components/CianGhostAiComponent.h"
#include "PacMan/Gameplay/Ghosts/Components/OrangeGhostAiComponent.h"
#include "PacMan/Gameplay/Ghosts/Components/PinkGhostAiComponent.h"
#include "PacMan/Gameplay/Ghosts/Components/RedGhostAiComponent.h"
#include "PacMan/Gameplay/MapLoading/Data/LoadedMapData.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"

namespace PacMan
{
	GhostsLoadingManager::GhostsLoadingManager(
		GEngine::GEngineCoreModules *modules,
		GEngine::Scene *scene,
		MapMovementManager *mapMovementManager,
		GameplayEntities *gameplayEntities,
		GhostsStateData* ghostsStateData
		) : _modules(modules),
		_scene(scene),
		_mapMovementManager(mapMovementManager),
		_gameplayEntities(gameplayEntities),
		_ghostsStateData(ghostsStateData)
	{
	}

	void GhostsLoadingManager::LoadGhosts(const LoadedMapData &loadedMapData)
	{
		GGAME_INFO("Starting ghosts loading.");

		_mapGhostInitialGridPosition = loadedMapData.MapGhostPosition;
		_ghostPrisionLeftSlotInitialGridPosition = loadedMapData.GhostPrisionLeftSlotGridPosition;
		_ghostPrisionCenterSlotInitialGridPosition = loadedMapData.GhostPrisionCenterSlotGridPosition;
		_ghostPrisionRightSlotInitialGridPosition = loadedMapData.GhostPrisionRightSlotGridPosition;

		_loadedGhostsData.MapGhostEntity = LoadGhost(
			GhostType::RED_GHOST,
			_mapGhostInitialGridPosition,
			false
			);
		_loadedGhostsData.LeftPrisionSlotGhostEntity = LoadGhost(
			GhostType::CIAN_GHOST,
			_ghostPrisionLeftSlotInitialGridPosition,
			true
			);
		_loadedGhostsData.CenterPrisionSlotGhostEntity = LoadGhost(
			GhostType::PINK_GHOST,
			_ghostPrisionCenterSlotInitialGridPosition,
			true
			);
		_loadedGhostsData.RightPrisionSlotGhostEntity = LoadGhost(
			GhostType::ORANGE_GHOST,
			_ghostPrisionRightSlotInitialGridPosition,
			true
			);

		GGAME_INFO("Ghosts loaded.");
	}

	const LoadedGhostsData & GhostsLoadingManager::GetLoadedGhostsData() const
	{
		return _loadedGhostsData;
	}

	void GhostsLoadingManager::SetGhostsToInitialPosition()
	{
		SetGhostToInitialPosition(
			_loadedGhostsData.MapGhostEntity,
			_mapGhostInitialGridPosition,
			false
			);
		SetGhostToInitialPosition(
			_loadedGhostsData.LeftPrisionSlotGhostEntity,
			_ghostPrisionLeftSlotInitialGridPosition,
			true
			);
		SetGhostToInitialPosition(
			_loadedGhostsData.CenterPrisionSlotGhostEntity,
			_ghostPrisionCenterSlotInitialGridPosition,
			true
			);
		SetGhostToInitialPosition(
			_loadedGhostsData.RightPrisionSlotGhostEntity,
			_ghostPrisionRightSlotInitialGridPosition,
			true
			);
	}

	std::shared_ptr<GEngine::Entity> GhostsLoadingManager::LoadGhost(const GhostType ghostType, const glm::i32vec2 &gridPosition, const bool isPrision)
	{
		const std::string ghostName = GetGhostName(ghostType);
		const GEngine::Color01 ghostColor = GetGhostColor(ghostType);

		const std::shared_ptr<GEngine::Entity> ghostEntity = _scene->AddWorldEntity().lock();
		ghostEntity->SetName("Ghost" + ghostName);

		ghostEntity->AddComponent<EntityIdComponent>().lock()->SetType(EntityType::GHOST);

		const std::shared_ptr<GEngine::Shape2dRendererComponent> shape = ghostEntity->AddComponent<GEngine::Shape2dRendererComponent>().lock();
		shape->SetLayer(1);
		shape->SetColor(ghostColor);

		const std::shared_ptr<GEngine::Collider2dComponent> collider = ghostEntity->AddComponent<GEngine::Collider2dComponent>().lock();
		collider->SetLayer(CollisionLayers::COLLISION_LAYER_GHOST);

		if (isPrision)
		{
			const glm::vec2 worldPosition = _mapMovementManager->GridPositionToWorldPosition(gridPosition, GEngine::CellPosition::CENTER_RIGHT);
			ghostEntity->GetTransform().lock()->SetPositionXY(worldPosition);
		}

		const std::shared_ptr<MapMovementComponent> mapMovement = ghostEntity->AddComponent<MapMovementComponent>().lock();
		mapMovement->SetCanAutomaticallyFindNextDirection(true);
		mapMovement->SetGuizmoColor(ghostColor.WithAlpha(0.6f));

		if (!isPrision)
		{
			mapMovement->SetGridPosition(gridPosition);
		}

		SetupGhostAi(ghostEntity.get(), mapMovement, ghostType);

		_gameplayEntities->Ghosts.push_back(ghostEntity);

		return ghostEntity;
	}

	void GhostsLoadingManager::SetGhostToInitialPosition(
		const std::weak_ptr<GEngine::Entity>& entity,
		const glm::i32vec2& gridPosition,
		const bool isPrision
		) const
	{
		const std::shared_ptr<GEngine::Entity> lEntity = entity.lock();
		if (!lEntity) return;

		const glm::vec2 worldPosition = _mapMovementManager->GridPositionToWorldPosition(
			gridPosition,
			GEngine::CellPosition::CENTER_RIGHT
			);

		lEntity->GetTransform().lock()->SetPositionXY(worldPosition);

		if (!isPrision)
		{
			const std::shared_ptr<MapMovementComponent> mapMovement = lEntity->GetComponent<MapMovementComponent>().lock();
			mapMovement->SetGridPosition(gridPosition);
		}
	}

	std::string GhostsLoadingManager::GetGhostName(const GhostType ghostType)
	{
		switch (ghostType)
		{
			case GhostType::RED_GHOST:
				return "Red";
			case GhostType::ORANGE_GHOST:
				return "Orange";
			case GhostType::CIAN_GHOST:
				return "Cian";
			case GhostType::PINK_GHOST:
				return "Pink";
		}

		return "Unknown";
	}

	GEngine::Color01 GhostsLoadingManager::GetGhostColor(const GhostType ghostType)
	{
		switch (ghostType)
		{
			case GhostType::RED_GHOST:
				return GEngine::Color01(1, 0, 0);
			case GhostType::ORANGE_GHOST:
				return GEngine::Color01(1, 0.3f, 0);
			case GhostType::CIAN_GHOST:
				return GEngine::Color01(0, 0.9f, 0.9f);
			case GhostType::PINK_GHOST:
				return GEngine::Color01(0.8, 0.3f, 0.7f);
		}

		return GEngine::Color01(0, 0, 0);;
	}

	void GhostsLoadingManager::SetupGhostAi(
		GEngine::Entity *ghostEntity,
		const std::weak_ptr<MapMovementComponent>& mapMovement,
		const GhostType ghostType
		) const
	{
		switch (ghostType)
		{
			case GhostType::RED_GHOST:
			{
				ghostEntity->AddComponent<RedGhostAiComponent>(_ghostsStateData, mapMovement);
				break;
			}
			case GhostType::ORANGE_GHOST:
			{
				ghostEntity->AddComponent<OrangeGhostAiComponent>(_ghostsStateData, mapMovement);
				break;
			}
			case GhostType::CIAN_GHOST:
			{
				ghostEntity->AddComponent<CianGhostAiComponent>(_ghostsStateData, mapMovement);
				break;
			}
			case GhostType::PINK_GHOST:
			{
				ghostEntity->AddComponent<PinkGhostAiComponent>(_ghostsStateData, mapMovement);
				break;
			}
		}
	}
}
