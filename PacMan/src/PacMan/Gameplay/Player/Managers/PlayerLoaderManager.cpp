//
// Created by guillem on 11/26/25.
//

#include "PlayerLoaderManager.h"

#include "PlayerCollisionsManager.h"
#include "GEngine/Components/Collider2dComponent.h"
#include "GEngine/Components/Shape2dRendererComponent.h"
#include "GEngine/Components/Sprite2dAnimatorComponent.h"
#include "GEngine/Components/Sprite2dRendererComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Entities/Entity.h"
#include "GEngine/Logging/GEngineLog.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Resources/SpriteResource.h"
#include "GEngine/Scenes/Scene.h"
#include "PacMan/Gameplay/Collisions/Enums/CollisionLayers.h"
#include "PacMan/Gameplay/Entities/Components/EntityIdComponent.h"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"
#include "PacMan/Gameplay/Input/Systems/PlayerInputSystem.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"
#include "PacMan/Gameplay/Player/Components/PlayerAnimationComponent.h"

namespace PacMan
{
	PlayerLoaderManager::PlayerLoaderManager(
		GEngine::GEngineCoreModules *modules,
		GEngine::Scene *scene,
		MapMovementManager* mapMovementManager,
		PlayerInputSystem* playerInputSystem,
		GameplayEntities* gameplayEntities,
		PlayerCollisionsManager* playerCollisionsManager,
		MapPathfindingManager* mapPathfindingManager
		)
		: _modules(modules),
		_scene(scene),
		_mapMovementManager(mapMovementManager),
		_playerInputSystem(playerInputSystem),
		_gameplayEntities(gameplayEntities),
		_playerCollisionsManager(playerCollisionsManager),
		_mapPathfindingManager(mapPathfindingManager)
	{
	}

	void PlayerLoaderManager::LoadPlayer(const glm::i32vec2& gridPosition)
	{
		GGAME_INFO("Starting player loading.");

		_playerInitialGridPosition = gridPosition;

		const GEngine::Color01 color = {0.9f, 0.9f, 0.1f};

		const std::shared_ptr<GEngine::Entity> playerEntity = _scene->AddWorldEntity().lock();
		playerEntity->SetName("Player");

		playerEntity->AddComponent<EntityIdComponent>().lock()->SetType(EntityType::PLAYER);

	 	const std::weak_ptr<GEngine::SpriteResource> spriteResource = _modules->resources->GetResource<GEngine::SpriteResource>("pacman.sprite");

		const std::shared_ptr<GEngine::Sprite2dRendererComponent> spriteRenderer = playerEntity->AddComponent<GEngine::Sprite2dRendererComponent>().lock();
		spriteRenderer->SetLayer(1);

		const std::shared_ptr<GEngine::Sprite2dAnimatorComponent> spriteAnimator = playerEntity->AddComponent<GEngine::Sprite2dAnimatorComponent>().lock();
		spriteAnimator->SetSprite2dRenderer(spriteRenderer);
		spriteAnimator->AddAnimation({"test", spriteResource, {0, 1}});

		const std::shared_ptr<GEngine::Collider2dComponent> collider = playerEntity->AddComponent<GEngine::Collider2dComponent>().lock();
		collider->SetLayer(CollisionLayers::COLLISION_LAYER_PLAYER);
		collider->SetLayerMask(CollisionLayers::COLLISION_LAYER_GHOST | CollisionLayers::COLLISION_LAYER_PELLETS);
		collider->OnContactStart().Add(std::bind(&PlayerCollisionsManager::WhenPlayerCollided, _playerCollisionsManager, std::placeholders::_1));

		const std::shared_ptr<MapMovementComponent> mapMovement = playerEntity->AddComponent<MapMovementComponent>(
			_mapMovementManager,
			_mapPathfindingManager
		).lock();
		mapMovement->SetGuizmoColor(color);
		mapMovement->SetGridPosition(_playerInitialGridPosition);

		const std::shared_ptr<PlayerAnimationComponent> playerAnimation = playerEntity->AddComponent<PlayerAnimationComponent>(
			mapMovement,
			spriteRenderer,
			spriteAnimator
		).lock();

		_gameplayEntities->Player = playerEntity;
		_playerInputSystem->SetPlayer(mapMovement); // Todo: this is not needed, we should use _gameplayEntities->Player

		GGAME_INFO("Player loaded.");
	}

	void PlayerLoaderManager::SetPlayerToInitialPosition() const
	{
		const std::shared_ptr<GEngine::Entity> player = _gameplayEntities->Player.lock();
		if (!player) return;

		const std::shared_ptr<MapMovementComponent> mapMovement = player->GetComponent<MapMovementComponent>().lock();
		mapMovement->SetGridPosition(_playerInitialGridPosition);
	}
} // PacMan