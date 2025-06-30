//
// Created by guillem on 6/30/25.
//

#ifndef PLAYERINPUTSYSTEM_H
#define PLAYERINPUTSYSTEM_H

#include <memory>

#include "GEngine/Systems/System.h"

namespace PacMan
{
	class GridMovementComponent;

	class PlayerInputSystem : public GEngine::System
	{
	public:
		PlayerInputSystem(const std::weak_ptr<GridMovementComponent>& component);

		void Tick() override;

		std::weak_ptr<GridMovementComponent> _component;
	};
}

#endif //PLAYERINPUTSYSTEM_H
