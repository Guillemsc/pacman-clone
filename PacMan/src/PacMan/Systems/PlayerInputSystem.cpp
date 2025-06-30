//
// Created by guillem on 6/30/25.
//

#include "PlayerInputSystem.h"

#include "raylib.h"
#include "PacMan/Components/GridMovementComponent.h"

namespace PacMan
{
	PlayerInputSystem::PlayerInputSystem(const std::weak_ptr<GridMovementComponent> &component)
	{
		_component = component;
	}

	void PlayerInputSystem::Tick()
	{
		GEngine::CardinalDirection direction = _component.lock()->NextDirection;

		if (IsKeyPressed(KEY_RIGHT))
		{
			direction = GEngine::CardinalDirection::RIGHT;
		}

		if (IsKeyPressed(KEY_LEFT))
		{
			direction = GEngine::CardinalDirection::LEFT;
		}

		if (IsKeyPressed(KEY_UP))
		{
			direction = GEngine::CardinalDirection::UP;
		}

		if (IsKeyPressed(KEY_DOWN))
		{
			direction = GEngine::CardinalDirection::DOWN;
		}

		_component.lock()->NextDirection = direction;
	}
} // PacMan