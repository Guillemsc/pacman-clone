//
// Created by guillem on 12/4/25.
//

#include "PelletsLoadingManager.h"

#include <format>

#include "GEngine/Components/Collider2dComponent.h"
#include "GEngine/Components/Shape2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Logging/GEngineLog.h"
#include "GEngine/Scenes/Scene.h"
#include "PacMan/Gameplay/Collisions/Enums/CollisionLayers.h"
#include "PacMan/Gameplay/Entities/Components/EntityIdComponent.h"
#include "PacMan/Gameplay/MapLoading/Data/LoadedMapData.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"

namespace PacMan
{
	PelletsLoadingManager::PelletsLoadingManager(
		GEngine::GEngineCoreModules *modules,
		GEngine::Scene *scene,
		MapMovementManager *mapMovementManager
		) : _modules(modules),
		_scene(scene),
		_mapMovementManager(mapMovementManager)
	{
	}

	void PelletsLoadingManager::LoadPellets(const LoadedMapData &loadedMapData) const
	{
		GGAME_INFO("Starting pellets loading.");

		const std::shared_ptr<GEngine::Entity> parentEntity = _scene->AddWorldEntity().lock();
		parentEntity->SetName("Pellets");

		for (const glm::vec2& pelletPosition : loadedMapData.SmallPelletsPositions)
		{
			const glm::vec2 worldPosition = _mapMovementManager->GridPositionToWorldPosition(pelletPosition);

			const std::shared_ptr<GEngine::Entity> entity = _scene->AddWorldEntity().lock();
			entity->SetParent(parentEntity);
			entity->SetName(std::format("Pellet: [{}, {}]", pelletPosition.x, pelletPosition.y));

			entity->AddComponent<EntityIdComponent>().lock()->SetType(EntityType::PELLET);

			const std::shared_ptr<GEngine::TransformComponent> transform = entity->GetComponent<GEngine::TransformComponent>().lock();
			transform->SetLocalScaleXY({0.2f, 0.2f});
			transform->SetPositionXY(worldPosition);

			const std::shared_ptr<GEngine::Shape2dRendererComponent> shapeRenderer = entity->AddComponent<GEngine::Shape2dRendererComponent>().lock();
			shapeRenderer->SetLayer(1);

			const std::shared_ptr<GEngine::Collider2dComponent> collider = entity->AddComponent<GEngine::Collider2dComponent>().lock();
			collider->SetLayer(CollisionLayers::COLLISION_LAYER_PELLETS);
		}

		for (const glm::vec2& pelletPosition : loadedMapData.BigPelletsPositions)
		{
			const glm::vec2 worldPosition = _mapMovementManager->GridPositionToWorldPosition(pelletPosition);

			const std::shared_ptr<GEngine::Entity> entity = _scene->AddWorldEntity().lock();
			entity->SetParent(parentEntity);
			entity->SetName(std::format("Big Pellet: [{}, {}]", pelletPosition.x, pelletPosition.y));

			entity->AddComponent<EntityIdComponent>().lock()->SetType(EntityType::BIG_PELLET);

			const std::shared_ptr<GEngine::TransformComponent> transform = entity->GetComponent<GEngine::TransformComponent>().lock();
			transform->SetLocalScaleXY({0.4f, 0.4f});
			transform->SetPositionXY(worldPosition);

			const std::shared_ptr<GEngine::Shape2dRendererComponent> shapeRenderer = entity->AddComponent<GEngine::Shape2dRendererComponent>().lock();
			shapeRenderer->SetLayer(1);

			const std::shared_ptr<GEngine::Collider2dComponent> collider = entity->AddComponent<GEngine::Collider2dComponent>().lock();
			collider->SetLayer(CollisionLayers::COLLISION_LAYER_PELLETS);
		}

		GGAME_INFO("Pellets loaded.");
	}
}
