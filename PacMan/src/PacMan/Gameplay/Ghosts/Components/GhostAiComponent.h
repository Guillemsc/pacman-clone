//
// Created by guillem on 11/28/25.
//

#ifndef GHOSTAICOMPONENT_H
#define GHOSTAICOMPONENT_H

#include "GhostStateComponent.h"
#include "GEngine/Colors/Color01.h"
#include "GEngine/Components/Component.h"
#include "glm/vec2.hpp"

namespace PacMan
{
	class MapMovementComponent;
	class GameplayEntities;
	struct GhostsStateData;

	class GhostAiComponent : public GEngine::Component
	{
		REGISTER_COMPONENT(GhostAiComponent)

	public:
		explicit GhostAiComponent(
			GEngine::GEngineCoreModules* modules,
			const std::weak_ptr<GEngine::Entity> &entity,
			GhostsStateData* ghostsStateData,
			GameplayEntities* gameplayEntities,
			const std::weak_ptr<GhostStateComponent>& ghostStateComponent,
			const std::weak_ptr<MapMovementComponent>& mapMovementComponent
			);

		void OnEnable() override;
		void OnTick() override;
		void OnDrawGuizmo() override;

		void TickPathfinding();
		void TickSpeed() const;

		void SetGuizmoColor(const GEngine::Color01& color);

	protected:
		virtual glm::i32vec2 GetChaseTargetGridPosition() const = 0;
		virtual glm::i32vec2 GetScatterTargetGridPosition() const = 0;

	private:
		glm::i32vec2 GetFrightenedTargetGridPosition() const;

	protected:
		GhostsStateData* const _ghostsStateData;
		GameplayEntities* const _gameplayEntities;
		std::weak_ptr<GhostStateComponent> _ghostStateComponent;
		std::weak_ptr<MapMovementComponent> _mapMovementComponent;

	private:
		glm::i32vec2 _previousTargetGridPosition = glm::i32vec2(0);
		glm::i32vec2 _validTargetGridPosition = glm::i32vec2(0);
		bool _hasValidPreviousTargetGridPosition = false;

		GEngine::Color01 _guizmoColor = {0, 1, 0, 1};
	};
}

#endif //GHOSTAICOMPONENT_H
