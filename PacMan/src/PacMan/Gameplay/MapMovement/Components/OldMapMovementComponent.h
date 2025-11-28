//
// Created by guillem on 6/29/25.
//

#ifndef GRIDMOVEMENTCOMPONENT_H
#define GRIDMOVEMENTCOMPONENT_H

#include "GEngine/Components/Component.h"
#include "GEngine/Directions/CardinalDirection.h"
#include "GEngine/Extensions/Vec2Extensions.h"
#include "glm/vec2.hpp"

namespace PacMan
{
	class OldMapMovementComponent final : public GEngine::Component
	{
	public:
		explicit OldMapMovementComponent(GEngine::GEngineCoreModules* modules, const std::weak_ptr<GEngine::Entity> &entity);

		constexpr const char* GetTypeName() override { return "Old Map Movement"; }

	public:
		glm::i32vec2 GridPosition = GEngine::Vec2Extensions::Int32Zero;
		GEngine::CardinalDirection Direction = GEngine::CardinalDirection::RIGHT;
		float ProgressToTarget = 0.0f;
		glm::i32vec2 TargetGridPosition = GEngine::Vec2Extensions::Int32Zero;
		float Speed = 0.1f;

		GEngine::CardinalDirection NextDirection = GEngine::CardinalDirection::RIGHT;
	};
}

#endif //GRIDMOVEMENTCOMPONENT_H
