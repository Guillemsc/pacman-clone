//
// Created by guillem on 11/28/25.
//

#ifndef GHOSTAICOMPONENT_H
#define GHOSTAICOMPONENT_H

#include "GEngine/Components/Component.h"
#include "glm/fwd.hpp"
#include "PacMan/Gameplay/MapMovement/Components/MapMovementComponent.h"

namespace PacMan
{
	class GhostAiComponent : public GEngine::Component
	{
		REGISTER_COMPONENT(GhostAiComponent)

	public:
		explicit GhostAiComponent(GEngine::GEngineCoreModules* modules, const std::weak_ptr<GEngine::Entity> &entity);

		void OnTick() override;

		void Init(const std::weak_ptr<MapMovementComponent>& mapMovementComponent);

	protected:
		virtual glm::i32vec2 GetChaseTargetGridPosition() const = 0;
		virtual glm::i32vec2 GetHideTargetGridPosition() const = 0;

	private:
		std::weak_ptr<MapMovementComponent> _mapMovementComponent;

		glm::i32vec2 _previousTargetGridPosition = glm::i32vec2(0);
	};
}

#endif //GHOSTAICOMPONENT_H
