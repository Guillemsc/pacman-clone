//
// Created by guillem on 6/30/25.
//

#include "PlayerInputSystem.h"

#include "raylib.h"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"
#include "PacMan/Gameplay/MapMovement/Components/OldMapMovementComponent.h"

namespace PacMan
{
	void PlayerInputSystem::Tick()
	{
		const std::shared_ptr<MapMovementComponent> component = _component.lock();
		if (!component) return;

		GEngine::CardinalDirection direction = GEngine::CardinalDirection::RIGHT;
		bool hasNextDirection = false;

		if (IsKeyPressed(KEY_RIGHT))
		{
			direction = GEngine::CardinalDirection::RIGHT;
			hasNextDirection = true;
		}

		if (IsKeyPressed(KEY_LEFT))
		{
			direction = GEngine::CardinalDirection::LEFT;
			hasNextDirection = true;
		}

		if (IsKeyPressed(KEY_UP))
		{
			direction = GEngine::CardinalDirection::UP;
			hasNextDirection = true;
		}

		if (IsKeyPressed(KEY_DOWN))
		{
			direction = GEngine::CardinalDirection::DOWN;
			hasNextDirection = true;
		}

		if (hasNextDirection)
		{
			component->SetNextDirection(direction);
		}
	}

	void PlayerInputSystem::SetPlayer(const std::weak_ptr<MapMovementComponent> &component)
	{
		_component = component;
	}
} // PacMan