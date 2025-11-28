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

namespace PacMan
{
	class MapMovementManager;

	class MapPathfindingManager
	{
	public:
		explicit MapPathfindingManager(MapMovementManager* mapMovementManager);

		void GeneratePath(
			const glm::i32vec2& originGridPosition,
			const glm::i32vec2& targetGridPosition,
			std::vector<glm::i32vec2>& generatedPath
			);

		void GenerateWalkableNeighbors(
			const glm::i32vec2& originGridPosition,
			std::vector<glm::i32vec2>& generatedPath
			);

	private:
		void GenerateNeighbors(const glm::i32vec2& gridPosition);

	private:
		MapMovementManager* const _mapMovementManager;

		std::priority_queue<std::shared_ptr<PathfindingNode>, std::vector<std::shared_ptr<PathfindingNode>>, PathfindingComparer> _checkingNodes;
		std::unordered_set<glm::i32vec2, GEngine::Vec2IntHash> _checkedNodes;
		std::vector<glm::i32vec2> _neighborsBuffer;
	};
}

#endif //MAPPATHFINDINGMANAGER_H
