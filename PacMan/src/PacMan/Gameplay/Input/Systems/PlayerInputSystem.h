//
// Created by guillem on 6/30/25.
//

#ifndef PLAYERINPUTSYSTEM_H
#define PLAYERINPUTSYSTEM_H

#include <memory>

#include "GEngine/Systems/System.h"

namespace PacMan
{
	class MapMovementComponent;

	class PlayerInputSystem : public GEngine::System
	{
	public:
		explicit PlayerInputSystem(const std::weak_ptr<MapMovementComponent>& component);

		void Tick() override;

		std::weak_ptr<MapMovementComponent> _component;
	};
}

#endif //PLAYERINPUTSYSTEM_H
