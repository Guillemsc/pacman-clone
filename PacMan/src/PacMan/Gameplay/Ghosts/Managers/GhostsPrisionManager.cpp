//
// Created by guillem on 11/28/25.
//

#include "GhostsPrisionManager.h"

#include "GEngine/Components/TransformComponent.h"
#include "GEngine/Coroutines/Coroutines.h"
#include "GEngine/Modules/TweensModule.h"
#include "GEngine/Tweens/InterpolationTween.h"
#include "GEngine/Tweens/Tween.h"
#include "PacMan/Gameplay/Ghosts/Data/GhostPrisionSlotData.h"
#include "PacMan/Gameplay/Ghosts/Data/LoadedGhostsData.h"
#include "PacMan/Gameplay/MapLoading/Data/LoadedMapData.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"

namespace PacMan
{
	GhostsPrisionManager::GhostsPrisionManager(
		GEngine::GEngineCoreModules* modules,
		MapMovementManager *mapMovementManager
		)
		: _modules(modules),
		_mapMovementManager(mapMovementManager)
	{
	}

	void GhostsPrisionManager::Setup(const LoadedMapData &loadedMapData, const LoadedGhostsData &loadedGhostsData)
	{
		_leftSlot = std::make_unique<GhostPrisionSlotData>(
			loadedMapData.GhostPrisionLeftSlotPosition,
			loadedGhostsData.LeftPrisionSlotGhostEntity
			);

		_centerSlot = std::make_unique<GhostPrisionSlotData>(
			loadedMapData.GhostPrisionCenterSlotPosition,
			loadedGhostsData.CenterPrisionSlotGhostEntity
			);

		_rightSlot = std::make_unique<GhostPrisionSlotData>(
			loadedMapData.GhostPrisionRightSlotPosition,
			loadedGhostsData.RightPrisionSlotGhostEntity
			);

		_prisionExitGridPosition = loadedMapData.PrisionExitPosition;
		_prisionExitPosition = _mapMovementManager->GridPositionToWorldPosition(_prisionExitGridPosition, GEngine::CellPosition::CENTER_RIGHT);

		_timeSinceLastGhostReleasedTimer.Start();
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

		GEngine::Coroutines::Start(&GhostsPrisionManager::PlayReleaseGhostAsync, this, ghostEntity).Forget();
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

	tokoro::Async<void> GhostsPrisionManager::PlayReleaseGhostAsync(const std::shared_ptr<GEngine::Entity> ghostEntity)
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

		co_await _modules->tweens->PlayAsync(tween);

		const std::shared_ptr<MapMovementComponent> mapMovement = ghostEntity->GetComponent<MapMovementComponent>().lock();
		mapMovement->SetGridPosition(_prisionExitGridPosition, GEngine::CellPosition::CENTER_RIGHT);

		co_return;
	}
} // PacMan