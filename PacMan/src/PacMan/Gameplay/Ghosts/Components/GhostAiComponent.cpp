//
// Created by guillem on 11/28/25.
//

#include "GhostAiComponent.h"

#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Modules/RenderingModule.h"
#include "glm/vec2.hpp"
#include "PacMan/Gameplay/Entities/Data/GameplayEntities.h"
#include "PacMan/Gameplay/Ghosts/Data/GhostsStateData.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"
#include "PacMan/Gameplay/MapMovement/Managers/MapMovementManager.h"

namespace PacMan
{
	GhostAiComponent::GhostAiComponent(
		GEngine::GEngineCoreModules *modules,
		const std::weak_ptr<GEngine::Entity> &entity,
		GhostsStateData* ghostsStateData,
		GameplayEntities* gameplayEntities,
		const std::weak_ptr<GhostStateComponent>& ghostStateComponent,
		const std::weak_ptr<MapMovementComponent>& mapMovementComponent
		)
		: Component(modules, entity),
		_ghostsStateData(ghostsStateData),
		_gameplayEntities(gameplayEntities),
		_ghostStateComponent(ghostStateComponent),
		_mapMovementComponent(mapMovementComponent)
	{
	}

	void GhostAiComponent::OnEnable()
	{
		_hasValidPreviousTargetGridPosition = false;
	}

	void GhostAiComponent::OnTick()
	{
		TickPathfinding();
		TickSpeed();
	}

	void GhostAiComponent::OnDrawGuizmo()
	{
		if (!_hasValidPreviousTargetGridPosition) return;

		const std::shared_ptr<MapMovementComponent> mapMovement = _mapMovementComponent.lock();
		if (!mapMovement) return;

		const glm::vec2 targetWorldPosition = mapMovement->GetMapMovementManager()->GridPositionToWorldPosition(_validTargetGridPosition);

		modules->rendering->Guizmo2dRender()->AddRect(targetWorldPosition, {6, 6}, 0, _guizmoColor);
	}

	void GhostAiComponent::TickPathfinding()
	{
		const std::shared_ptr<MapMovementComponent> mapMovement = _mapMovementComponent.lock();
		if (!mapMovement) return;

		glm::i32vec2 targetGridPosition;

		switch (_ghostsStateData->ghostsMode)
		{
			case GhostMode::CHASE:
			{
				targetGridPosition = GetChaseTargetGridPosition();
				break;
			}

			case GhostMode::SCATTER:
			{
				targetGridPosition = GetScatterTargetGridPosition();
				break;
			}

			case GhostMode::FRIGHTENED:
			{
				targetGridPosition = GetFrightenedTargetGridPosition();
				break;
			}
		}

		bool targetChanged = targetGridPosition != _previousTargetGridPosition || !_hasValidPreviousTargetGridPosition;

		if (!targetChanged && _hasValidPreviousTargetGridPosition)
		{
			if (mapMovement->GetIsMovingRandomly())
			{
				const float distance = GEngine::Vec2Extensions::Distance(_validTargetGridPosition, mapMovement->GetGridPosition());

				if (distance > 4)
				{
					targetChanged = true;
				}
			}
		}

		if (targetChanged)
		{
			const PathfindingResult pathfindingResult = mapMovement->PathfindToGridPosition(targetGridPosition);

			if (pathfindingResult.couldReachAnyPosition)
			{
				_previousTargetGridPosition = targetGridPosition;
				_validTargetGridPosition = pathfindingResult.realTargetGridPosition;
				_hasValidPreviousTargetGridPosition = true;
			}
		}
	}

	void GhostAiComponent::TickSpeed() const
	{
		const std::shared_ptr<GhostStateComponent> ghostState = _ghostStateComponent.lock();
		if (!ghostState) return;

		const std::shared_ptr<MapMovementComponent> mapMovement = _mapMovementComponent.lock();
		if (!mapMovement) return;

		float speed = 40.0f;

		if (ghostState->isReturningToPrision)
		{
			speed = 50.0f;
		}
		else if (_ghostsStateData->ghostsMode == GhostMode::FRIGHTENED)
		{
			speed = 20.0f;
		}

		mapMovement->SetMovementSpeed(speed);
	}

	void GhostAiComponent::SetGuizmoColor(const GEngine::Color01 &color)
	{
		_guizmoColor = color;
	}

	glm::i32vec2 GhostAiComponent::GetFrightenedTargetGridPosition() const
	{
		const std::shared_ptr<MapMovementComponent> mapMovement = _mapMovementComponent.lock();
		if (!mapMovement) return glm::i32vec2(0);

		const std::shared_ptr<GEngine::Entity> player = _gameplayEntities->Player.lock();
		if (!player) return glm::i32vec2(0);

		const std::shared_ptr<MapMovementComponent> playerMapMovement = player->GetComponent<MapMovementComponent>().lock();

		const glm::i32vec2 distance = playerMapMovement->GetGridPosition() - mapMovement->GetGridPosition();

		return mapMovement->GetGridPosition() - (distance * 2);
	}
} // PacMan