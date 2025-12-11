//
// Created by guillem on 11/27/25.
//

#ifndef MAPPATHFINDINGMANAGER_H
#define MAPPATHFINDINGMANAGER_H

#include <queue>
#include <unordered_set>
#include <vector>

#include "GEngine/Hashes/Vec2IntHash.h"
#include "PacMan/Gameplay/MapMovement/Comparers/PathfindingComparer.h"
#include "PacMan/Gameplay/MapMovement/Data/PathfindingNode.h"
#include "PacMan/Gameplay/MapMovement/Data/PathfindingResult.h"

namespace PacMan
{
	class MapMovementManager;

	class MapPathfindingManager
	{
	public:
		explicit MapPathfindingManager(MapMovementManager* mapMovementManager);

		PathfindingResult GeneratePath(
			const glm::i32vec2& originGridPosition,
			const glm::i32vec2& allowedDirection,
			const glm::i32vec2& targetGridPosition,
			std::vector<glm::i32vec2>& generatedPath
			);

		void GenerateWalkableNeighbors(
			const glm::i32vec2& originGridPosition,
			const glm::i32vec2 &allowedDirection,
			std::vector<glm::i32vec2>& generatedNeighbors
			);

	private:
		glm::i32vec2 GetDirectionFromParent(const PathfindingNode* pathfindingNode, const glm::i32vec2& defaultDirection);
		void GenerateNeighbors(const glm::i32vec2& gridPosition, const glm::i32vec2& allowedDirection);

	private:
		MapMovementManager* const _mapMovementManager;

		std::priority_queue<std::shared_ptr<PathfindingNode>, std::vector<std::shared_ptr<PathfindingNode>>, PathfindingComparer> _checkingNodes;
		std::unordered_set<glm::i32vec2, GEngine::Vec2IntHash> _checkedNodes;
		std::priority_queue<std::shared_ptr<PathfindingNode>, std::vector<std::shared_ptr<PathfindingNode>>, PathfindingComparer> _checkedNodesByDistance;
		std::vector<glm::i32vec2> _neighborsBuffer;
	};
}

#endif //MAPPATHFINDINGMANAGER_H
