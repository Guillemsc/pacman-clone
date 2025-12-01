//
// Created by guillem on 11/26/25.
//

#include "PlayerLoaderManager.h"

#include "GEngine/Components/Shape2dRendererComponent.h"
#include "GEngine/Components/Sprite2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Resources/SpriteResource.h"
#include "GEngine/Scenes/Scene.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"
#include "PacMan/Gameplay/Input/Systems/PlayerInputSystem.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"

namespace PacMan
{
	PlayerLoaderManager::PlayerLoaderManager(
		GEngine::GEngineCoreModules *modules,
		GEngine::Scene *scene,
		MapMovementManager* mapMovementManager,
		PlayerInputSystem* playerInputSystem,
		GameplayEntities* gameplayEntities
		)
		: _modules(modules),
		_scene(scene),
		_mapMovementManager(mapMovementManager),
		_playerInputSystem(playerInputSystem),
		_gameplayEntities(gameplayEntities)
	{
	}

	void PlayerLoaderManager::LoadPlayer(const glm::i32vec2& gridPosition) const
	{
		const std::shared_ptr<GEngine::Entity> playerEntity = _scene->AddWorldEntity().lock();
		playerEntity->SetName("Player");

	 	const std::weak_ptr<GEngine::SpriteResource> spriteResource = _modules->resources->GetResource<GEngine::SpriteResource>("pacman.sprite");

		//const std::shared_ptr<GEngine::Shape2dRendererComponent> shape = playerEntity->AddComponent<GEngine::Shape2dRendererComponent>().lock();
		//shape->SetLayer(1);

		const std::shared_ptr<GEngine::Sprite2dRendererComponent> spriteRenderer = playerEntity->AddComponent<GEngine::Sprite2dRendererComponent>().lock();
		spriteRenderer->SetSprite(spriteResource);
		spriteRenderer->SetLayer(1);

		const std::shared_ptr<MapMovementComponent> mapMovement = playerEntity->AddComponent<MapMovementComponent>().lock();
		mapMovement->SetGridPosition(gridPosition);
		_playerInputSystem->SetPlayer(mapMovement);

		_gameplayEntities->Player = playerEntity;
	}
} // PacMan