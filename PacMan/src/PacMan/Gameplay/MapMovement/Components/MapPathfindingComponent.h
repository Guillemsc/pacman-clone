//
// Created by guillem on 11/27/25.
//

#ifndef MAPPATHFINDINGCOMPONENT_H
#define MAPPATHFINDINGCOMPONENT_H

#include <memory>

#include "GEngine/Components/Component.h"
#include "GEngine/Extensions/Vec2Extensions.h"

namespace GEngine
{
	class GEngineCoreModules;
	class Entity;
}

namespace PacMan
{
	class OldMapMovementComponent;

	class MapPathfindingComponent final : public GEngine::Component
	{
	public:
		explicit MapPathfindingComponent(GEngine::GEngineCoreModules* modules, const std::weak_ptr<GEngine::Entity> &entity);

		constexpr const char* GetTypeName() override { return "Map Pathfinding"; }

	public:
		std::weak_ptr<OldMapMovementComponent> mapMovementComponent;

		glm::i32vec2 targetGridPosition = GEngine::Vec2Extensions::Int32Zero;
		bool hasValidTargetGridPosition = false;

		std::vector<glm::i32vec2> path;
		std::int32_t currentPathIndex = 0;
		glm::i32vec2 pathTargetGridPosition = GEngine::Vec2Extensions::Int32Zero;
	};
}

#endif //MAPPATHFINDINGCOMPONENT_H
