//
// Created by guillem on 12/4/25.
//

#include "PelletsLoadingManager.h"

#include "GEngine/Components/Shape2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Scenes/Scene.h"
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

	void PelletsLoadingManager::LoadPellets(const LoadedMapData &loadedMapData)
	{
		const std::shared_ptr<GEngine::Entity> parentEntity = _scene->AddWorldEntity().lock();
		parentEntity->SetName("Pellets");

		for (const glm::vec2& pelletPosition : loadedMapData.SmallPelletsPositions)
		{
			const std::shared_ptr<GEngine::Entity> entity = _scene->AddWorldEntity().lock();
			entity->SetParent(parentEntity);
			entity->SetName("Pellet");

			const std::shared_ptr<GEngine::TransformComponent> transform = entity->GetComponent<GEngine::TransformComponent>().lock();
			transform->SetLocalScaleXY({0.3f, 0.3f});

			const std::shared_ptr<GEngine::Shape2dRendererComponent> shapeRenderer = entity->AddComponent<GEngine::Shape2dRendererComponent>().lock();
			shapeRenderer->SetLayer(1);

			const glm::vec2 worldPosition = _mapMovementManager->GridPositionToWorldPosition(pelletPosition);
			transform->SetPositionXY(worldPosition);
		}
	}
}
