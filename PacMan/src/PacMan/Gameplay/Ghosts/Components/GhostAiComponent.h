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
	struct GhostsStateData;

	class GhostAiComponent : public GEngine::Component
	{
		REGISTER_COMPONENT(GhostAiComponent)

	public:
		explicit GhostAiComponent(
			GEngine::GEngineCoreModules* modules,
			const std::weak_ptr<GEngine::Entity> &entity,
			GhostsStateData* ghostsStateData,
			const std::weak_ptr<MapMovementComponent>& mapMovementComponent
			);

		void OnTick() override;

	protected:
		virtual glm::i32vec2 GetChaseTargetGridPosition() const = 0;
		virtual glm::i32vec2 GetHideTargetGridPosition() const = 0;

	private:
		GhostsStateData* const _ghostsStateData;
		std::weak_ptr<MapMovementComponent> _mapMovementComponent;

		glm::i32vec2 _previousTargetGridPosition = glm::i32vec2(0);
	};
}

#endif //GHOSTAICOMPONENT_H
