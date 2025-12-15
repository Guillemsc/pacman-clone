//
// Created by guillem on 11/27/25.
//

#include "GhostsLoadingManager.h"

#include "GEngine/Components/Collider2dComponent.h"
#include "GEngine/Components/Shape2dRendererComponent.h"
#include "GEngine/Components/Sprite2dAnimatorComponent.h"
#include "GEngine/Components/Sprite2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Logging/GEngineLog.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Scenes/Scene.h"
#include "PacMan/Gameplay/Collisions/Enums/CollisionLayers.h"
#include "PacMan/Gameplay/Entities/Components/EntityIdComponent.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"
#include "PacMan/Gameplay/Ghosts/Components/CianGhostAiComponent.h"
#include "PacMan/Gameplay/Ghosts/Components/GhostAnimationComponent.h"
#include "PacMan/Gameplay/Ghosts/Components/OrangeGhostAiComponent.h"
#include "PacMan/Gameplay/Ghosts/Components/PinkGhostAiComponent.h"
#include "PacMan/Gameplay/Ghosts/Components/RedGhostAiComponent.h"
#include "PacMan/Gameplay/MapLoading/Data/LoadedMapData.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"
#include "GEngine/Resources/SpriteResource.h"
#include "PacMan/Gameplay/Ghosts/Components/GhostStateComponent.h"

namespace PacMan
{
	GhostsLoadingManager::GhostsLoadingManager(
		GEngine::GEngineCoreModules *modules,
		GEngine::Scene *scene,
		MapMovementManager *mapMovementManager,
		MapPathfindingManager* mapPathfindingManager,
		GameplayEntities *gameplayEntities,
		GhostsStateData* ghostsStateData
		) : _modules(modules),
		_scene(scene),
		_mapMovementManager(mapMovementManager),
		_mapPathfindingManager(mapPathfindingManager),
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

		const std::weak_ptr<GhostStateComponent> ghostState = ghostEntity->AddComponent<GhostStateComponent>();

		const std::string movementResourcePath = std::format("ghosts/{}.sprite", ghostName);
		const std::weak_ptr<GEngine::SpriteResource> movementSpriteResource
			= _modules->resources->GetResource<GEngine::SpriteResource>(movementResourcePath);
		const std::weak_ptr<GEngine::SpriteResource> deadSpriteResource
			= _modules->resources->GetResource<GEngine::SpriteResource>("ghosts/dead.sprite");
		const std::weak_ptr<GEngine::SpriteResource> scaredSpriteResource
			= _modules->resources->GetResource<GEngine::SpriteResource>("ghosts/scared.sprite");

		const std::shared_ptr<GEngine::Sprite2dRendererComponent> spriteRenderer = ghostEntity->AddComponent<GEngine::Sprite2dRendererComponent>().lock();
		spriteRenderer->SetLayer(1);

		const std::shared_ptr<GEngine::Sprite2dAnimatorComponent> spriteAnimator = ghostEntity->AddComponent<GEngine::Sprite2dAnimatorComponent>().lock();
		spriteAnimator->SetSprite2dRenderer(spriteRenderer);

		spriteAnimator->AddAnimation({"move_right", movementSpriteResource, {0, 1}});
		spriteAnimator->AddAnimation({"move_left", movementSpriteResource, {2, 3}});
		spriteAnimator->AddAnimation({"move_up", movementSpriteResource, {4, 5}});
		spriteAnimator->AddAnimation({"move_down", movementSpriteResource, {6, 7}});

		spriteAnimator->AddAnimation({"dead_right", deadSpriteResource, {0}});
		spriteAnimator->AddAnimation({"dead_left", deadSpriteResource, {1}});
		spriteAnimator->AddAnimation({"dead_up", deadSpriteResource, {2}});
		spriteAnimator->AddAnimation({"dead_down", deadSpriteResource, {3}});

		spriteAnimator->AddAnimation({"scared", scaredSpriteResource, {0, 1}});
		spriteAnimator->AddAnimation({"scared_almost_finished", scaredSpriteResource, {0, 1, 2, 3}});

		const std::shared_ptr<GEngine::Collider2dComponent> collider = ghostEntity->AddComponent<GEngine::Collider2dComponent>().lock();
		const std::uint32_t collisionLayer = isPrision ? CollisionLayers::COLLISION_LAYER_DEFAULT : CollisionLayers::COLLISION_LAYER_GHOST;
		collider->SetLayer(collisionLayer);
		collider->SetSize({6, 6});

		if (isPrision)
		{
			const glm::vec2 worldPosition = _mapMovementManager->GridPositionToWorldPosition(gridPosition, GEngine::CellPosition::CENTER_RIGHT);
			ghostEntity->GetTransform().lock()->SetPositionXY(worldPosition);
		}

		const std::shared_ptr<MapMovementComponent> mapMovement = ghostEntity->AddComponent<MapMovementComponent>(
			_mapMovementManager,
			_mapPathfindingManager
			).lock();
		mapMovement->SetCanAutomaticallyFindNextDirection(true);
		mapMovement->SetGuizmoColor(ghostColor.WithAlpha(0.6f));

		if (!isPrision)
		{
			mapMovement->SetGridPosition(gridPosition);
		}

		ghostEntity->AddComponent<GhostAnimationComponent>(
			_ghostsStateData,
			ghostState,
			mapMovement,
			spriteRenderer,
			spriteAnimator
			);

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
				return "red";
			case GhostType::ORANGE_GHOST:
				return "orange";
			case GhostType::CIAN_GHOST:
				return "cian";
			case GhostType::PINK_GHOST:
				return "pink";
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
				ghostEntity->AddComponent<RedGhostAiComponent>(
					_ghostsStateData,
					_gameplayEntities,
					mapMovement
					);
				break;
			}
			case GhostType::ORANGE_GHOST:
			{
				ghostEntity->AddComponent<OrangeGhostAiComponent>(
					_ghostsStateData,
					_gameplayEntities,
					mapMovement
					);
				break;
			}
			case GhostType::CIAN_GHOST:
			{
				ghostEntity->AddComponent<CianGhostAiComponent>(
					_ghostsStateData,
					_gameplayEntities,
					mapMovement
					);
				break;
			}
			case GhostType::PINK_GHOST:
			{
				ghostEntity->AddComponent<PinkGhostAiComponent>(
					_ghostsStateData,
					_gameplayEntities,
					mapMovement
					);
				break;
			}
		}
	}
}
