//
// Created by guillem on 6/30/25.
//

#ifndef PLAYERINPUTSYSTEM_H
#define PLAYERINPUTSYSTEM_H

#include <memory>

#include "GEngine/Tickables/Tickable.h"

namespace PacMan
{
	class MapMovementComponent;

	class PlayerInputSystem : public GEngine::Tickable
	{
	public:
		void Tick() override;

		void SetPlayer(const std::weak_ptr<MapMovementComponent>& component);

		std::weak_ptr<MapMovementComponent> _component;
	};
}

#endif //PLAYERINPUTSYSTEM_H
