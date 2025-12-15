//
// Created by guillem on 11/28/25.
//

#include "GhostsPrisionManager.h"

#include "GEngine/Components/Collider2dComponent.h"
#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Coroutines/CoroutinesRunner.h"
#include "GEngine/Extensions/VectorExtensions.h"
#include "GEngine/Modules/TweensModule.h"
#include "GEngine/Tweens/InterpolationTween.h"
#include "GEngine/Tweens/Tween.h"
#include "PacMan/Gameplay/Collisions/Enums/CollisionLayers.h"
#include "PacMan/Gameplay/Ghosts/Components/GhostAiComponent.h"
#include "PacMan/Gameplay/Ghosts/Components/GhostStateComponent.h"
#include "PacMan/Gameplay/Ghosts/Data/GhostPrisionSlotData.h"
#include "PacMan/Gameplay/Ghosts/Data/GhostsStateData.h"
#include "PacMan/Gameplay/Ghosts/Data/LoadedGhostsData.h"
#include "PacMan/Gameplay/MapLoading/Data/LoadedMapData.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"

namespace PacMan
{
	GhostsPrisionManager::GhostsPrisionManager(
		GEngine::GEngineCoreModules* modules,
		GEngine::CoroutinesRunner* coroutines,
		MapMovementManager *mapMovementManager,
		GhostsStateData* ghostsStateData
		)
		: _modules(modules),
		_coroutines(coroutines),
		_mapMovementManager(mapMovementManager),
		_ghostsStateData(ghostsStateData)
	{
		_cancellationTokenSource = std::make_shared<GEngine::CancellationTokenSource>();
	}

	void GhostsPrisionManager::Setup(const LoadedMapData &loadedMapData, const LoadedGhostsData &loadedGhostsData)
	{
		_loadedGhostsData = loadedGhostsData;

		_leftSlot = std::make_unique<GhostPrisionSlotData>(loadedGhostsData.LeftPrisionSlotGhostEntity);
		_centerSlot = std::make_unique<GhostPrisionSlotData>(loadedGhostsData.CenterPrisionSlotGhostEntity);
		_rightSlot = std::make_unique<GhostPrisionSlotData>(loadedGhostsData.RightPrisionSlotGhostEntity);

		_prisionExitGridPosition = loadedMapData.PrisionExitPosition;

		_prisionExitPosition = _mapMovementManager->GridPositionToWorldPosition(
			_prisionExitGridPosition,
			GEngine::CellPosition::CENTER_RIGHT
			);

		_prisionReturnPosition = _mapMovementManager->GridPositionToWorldPosition(
			loadedMapData.GhostPrisionCenterSlotGridPosition,
			GEngine::CellPosition::CENTER_RIGHT
			);

		_timeSinceLastGhostReleasedTimer.Start();
	}

	void GhostsPrisionManager::Stop()
	{
		_cancellationTokenSource->Cancel();
		_cancellationTokenSource = std::make_shared<GEngine::CancellationTokenSource>();

		_timeSinceLastGhostReleasedTimer.Reset();
	}

	void GhostsPrisionManager::Reset()
	{
		_leftSlot->ghostEntity = _loadedGhostsData.LeftPrisionSlotGhostEntity;
		_centerSlot->ghostEntity = _loadedGhostsData.CenterPrisionSlotGhostEntity;
		_rightSlot->ghostEntity = _loadedGhostsData.RightPrisionSlotGhostEntity;

		_timeSinceLastGhostReleasedTimer.Start();
	}

	void GhostsPrisionManager::KillGhostAndStartPathBackToPrision(const std::weak_ptr<GEngine::Entity> &ghost)
	{
		const std::shared_ptr<GEngine::Entity> lGhost = ghost.lock();
		if (!lGhost) return;

		const std::shared_ptr<MapMovementComponent> mapMovement = lGhost->GetComponent<MapMovementComponent>().lock();
		if (!mapMovement) return;

		const std::shared_ptr<GhostAiComponent> ai = lGhost->GetComponent<GhostAiComponent>().lock();
		if (!ai) return;

		const std::shared_ptr<GEngine::Collider2dComponent> collider = lGhost->GetComponent<GEngine::Collider2dComponent>().lock();
		if (!collider) return;

		const std::shared_ptr<GhostStateComponent> state = lGhost->GetComponent<GhostStateComponent>().lock();
		if (!state) return;

		collider->SetLayer(CollisionLayers::COLLISION_LAYER_DEFAULT);
		ai->SetEnabled(false);
		state->isReturningToPrision = true;

		_coroutines->Start(
			&GhostsPrisionManager::PlayReturnGhostAsync,
			this,
			lGhost,
			_cancellationTokenSource->GetToken()
			).Forget();
	}

	void GhostsPrisionManager::Tick()
	{
		if (_timeSinceLastGhostReleasedTimer.GetTimeSeconds() > 3)
		{
			ReleaseNextGhost();

			_timeSinceLastGhostReleasedTimer.Restart();
		}
	}

	void GhostsPrisionManager::ReleaseNextGhost()
	{
		GhostPrisionSlotData* slot = GetNextSlotToReleaseOrNull();
		if (slot == nullptr) return;

		const std::shared_ptr<GEngine::Entity> ghostEntity = slot->ghostEntity.lock();
		slot->ghostEntity.reset();

		_coroutines->Start(
			&GhostsPrisionManager::PlayReleaseGhostAsync,
			this,
			ghostEntity,
			_cancellationTokenSource->GetToken()
			).Forget();
	}

	GhostPrisionSlotData* GhostsPrisionManager::GetNextSlotToReleaseOrNull() const
	{
		if (!_centerSlot->ghostEntity.expired())
		{
			return _centerSlot.get();
		}

		if (!_leftSlot->ghostEntity.expired())
		{
			return _leftSlot.get();
		}

		if (!_rightSlot->ghostEntity.expired())
		{
			return _rightSlot.get();
		}

		return nullptr;
	}

	tokoro::Async<void> GhostsPrisionManager::PlayReleaseGhostAsync(
		const std::shared_ptr<GEngine::Entity> ghostEntity,
		const GEngine::CancellationToken cancellationToken
		)
	{
		const std::shared_ptr<GEngine::TransformComponent> transform = ghostEntity->GetTransform().lock();
		const glm::vec2 position = transform->GetPositionXY();

		const float distanceToCenter = glm::distance(position.x, _prisionExitPosition.x);
		const float distanceToHeight = glm::distance(position.y, _prisionExitPosition.y);

		const float timeToCenter = distanceToCenter * 0.1f;
		const float timeToHeight = distanceToHeight * 0.1f;

		const std::shared_ptr<GEngine::Tween> tween = std::make_shared<GEngine::Tween>();

		tween->AddChildren(std::make_shared<GEngine::InterpolationTween<float>>(
			[transform] { return transform->GetPosition().x; },
			[transform](const float value) { transform->SetLocalPositionX(value); },
			_prisionExitPosition.x,
			timeToCenter
			));

		tween->AddChildren(std::make_shared<GEngine::InterpolationTween<float>>(
			[transform] { return transform->GetPosition().y; },
			[transform](const float value) { transform->SetLocalPositionY(value); },
			_prisionExitPosition.y,
			timeToHeight
			));

		co_await _modules->tweens->PlayAsync(tween, cancellationToken);
		if (cancellationToken.IsCancelled()) co_return;

		const std::shared_ptr<MapMovementComponent> mapMovement = ghostEntity->GetComponent<MapMovementComponent>().lock();
		mapMovement->SetGridPosition(_prisionExitGridPosition, GEngine::CellPosition::CENTER_RIGHT);
		mapMovement->SetCanMove(true);
		mapMovement->SetCanAutomaticallyFindNextDirection(true);
		mapMovement->SetCanAutomaticallyKeepMovingOnCurrentDirection(true);

		const std::shared_ptr<GEngine::Collider2dComponent> collider = ghostEntity->GetComponent<GEngine::Collider2dComponent>().lock();
		collider->SetLayer(CollisionLayers::COLLISION_LAYER_GHOST);

		const std::shared_ptr<GhostAiComponent> ai = ghostEntity->GetComponent<GhostAiComponent>().lock();
		ai->SetEnabled(true);

		const std::shared_ptr<GhostStateComponent> state = ghostEntity->GetComponent<GhostStateComponent>().lock();
		state->isReturningToPrision = false;
	}

	tokoro::Async<void> GhostsPrisionManager::PlayReturnGhostAsync(
		const std::shared_ptr<GEngine::Entity> ghostEntity,
		const GEngine::CancellationToken cancellationToken
		)
	{
		const std::shared_ptr<GEngine::TransformComponent> transform = ghostEntity->GetTransform().lock();

		const std::shared_ptr<MapMovementComponent> mapMovement = ghostEntity->GetComponent<MapMovementComponent>().lock();

		mapMovement->SetCanAutomaticallyFindNextDirection(false);
		mapMovement->SetCanAutomaticallyKeepMovingOnCurrentDirection(false);
		mapMovement->PathfindToGridPosition(_prisionExitGridPosition);
		mapMovement->SetMovementSpeed(60);

		while (mapMovement->GetGridPosition() != _prisionExitGridPosition)
		{
			if (cancellationToken.IsCancelled()) co_return;
			co_await tokoro::Wait();
		}

		const glm::vec2 position = transform->GetPositionXY();

		const float distanceToCenter = glm::distance(position.x, _prisionExitPosition.x);
		const float distanceToHeight = glm::distance(position.y, _prisionReturnPosition.y);

		const float timeToCenter = distanceToCenter * 0.1f;
		const float timeToHeight = distanceToHeight * 0.1f;

		const std::shared_ptr<GEngine::Tween> tween = std::make_shared<GEngine::Tween>();

		tween->AddChildren(std::make_shared<GEngine::InterpolationTween<float>>(
			[transform] { return transform->GetPosition().x; },
			[transform](const float value) { transform->SetLocalPositionX(value); },
			_prisionExitPosition.x,
			timeToCenter
			));

		tween->AddChildren(std::make_shared<GEngine::InterpolationTween<float>>(
			[transform] { return transform->GetPosition().y; },
			[transform](const float value) { transform->SetLocalPositionY(value); },
			_prisionReturnPosition.y,
			timeToHeight
			));

		co_await _modules->tweens->PlayAsync(tween, cancellationToken);
		if (cancellationToken.IsCancelled()) co_return;

		transform->SetLocalScaleXY({1, 1});

		co_await PlayReleaseGhostAsync(ghostEntity, cancellationToken);
	}
} // PacMan