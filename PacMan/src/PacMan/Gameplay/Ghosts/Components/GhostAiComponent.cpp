//
// Created by guillem on 11/28/25.
//

#include "GhostAiComponent.h"

#include "glm/vec2.hpp"

namespace PacMan
{
	GhostAiComponent::GhostAiComponent(GEngine::GEngineCoreModules *modules, const std::weak_ptr<GEngine::Entity> &entity)
		: Component(modules, entity)
	{
	}

	void GhostAiComponent::OnTick()
	{
		const std::shared_ptr<MapMovementComponent> mapMovement = _mapMovementComponent.lock();
		if (!mapMovement) return;

		const glm::i32vec2 targetGridPosition = GetChaseTargetGridPosition();

		const bool targetChanged = targetGridPosition != _previousTargetGridPosition;

		if (targetChanged)
		{
			mapMovement->PathfindToGridPosition(targetGridPosition);
		}
	}

	void GhostAiComponent::Init(const std::weak_ptr<MapMovementComponent> &mapMovementComponent)
	{
		_mapMovementComponent = mapMovementComponent;
	}
} // PacMan