//
// Created by guillem on 11/27/25.
//

#include "MapPathfindingManager.h"

#include <algorithm>

#include "MapMovementManager.h"
#include "GEngine/Extensions/Vec2Extensions.h"
#include "GEngine/Hashes/Vec2IntHash.h"

namespace PacMan
{
	MapPathfindingManager::MapPathfindingManager(MapMovementManager *mapMovementManager)
		: _mapMovementManager(mapMovementManager)
	{

	}

	void MapPathfindingManager::GeneratePath(
		const glm::i32vec2 &originGridPosition,
		const glm::i32vec2 &targetGridPosition,
		std::vector<glm::i32vec2> &generatedPath
		)
	{
		generatedPath.clear();

		const std::shared_ptr<PathfindingNode> initialNode = std::make_shared<PathfindingNode>(
			originGridPosition,
			GEngine::Vec2Extensions::Distance(originGridPosition, targetGridPosition),
			nullptr
			);
		_checkingNodes.push(initialNode);

		std::shared_ptr<PathfindingNode> foundNode;
		bool nodeFound = false;

		while (!_checkingNodes.empty())
		{
			std::shared_ptr<PathfindingNode> currentNode = _checkingNodes.top();

			if (currentNode->position == targetGridPosition)
			{
				foundNode = currentNode;
				nodeFound = true;
				break;
			}

			_checkingNodes.pop();
			_checkedNodes.insert(currentNode->position);

			GenerateNeighbors(currentNode->position);

			for (glm::i32vec2 neighbor : _neighborsBuffer)
			{
				const bool isWalkable = _mapMovementManager->IsWalkable(neighbor);
				if (!isWalkable) continue;

				const bool alreadyChecked = _checkedNodes.contains(neighbor);
				if (alreadyChecked) continue;

				const std::shared_ptr<PathfindingNode> newNode = std::make_shared<PathfindingNode>(
					neighbor,
					GEngine::Vec2Extensions::Distance(neighbor, targetGridPosition),
					currentNode
					);
				_checkingNodes.push(newNode);
			}
		}

		_checkingNodes = std::priority_queue<std::shared_ptr<PathfindingNode>, std::vector<std::shared_ptr<PathfindingNode>>, PathfindingComparer>();
		_checkedNodes.clear();

		if (!nodeFound) return;

		std::shared_ptr<PathfindingNode> checkingNode = foundNode;

		while (checkingNode->position != originGridPosition)
		{
			generatedPath.push_back(checkingNode->position);

			checkingNode = checkingNode->parent;
		}

		std::ranges::reverse(generatedPath);
	}

	void MapPathfindingManager::GenerateWalkableNeighbors(
		const glm::i32vec2 &originGridPosition,
		std::vector<glm::i32vec2> &generatedPath
		)
	{
		generatedPath.clear();

		GenerateNeighbors(originGridPosition);

		for (glm::i32vec2 neighbor : _neighborsBuffer)
		{
			const bool isWalkable = _mapMovementManager->IsWalkable(neighbor);
			if (!isWalkable) continue;

			generatedPath.push_back(neighbor);
		}
	}

	void MapPathfindingManager::GenerateNeighbors(const glm::i32vec2 &gridPosition)
	{
		_neighborsBuffer.clear();
		_neighborsBuffer.push_back(gridPosition + glm::i32vec2(1, 0));
		_neighborsBuffer.push_back(gridPosition + glm::i32vec2(-1, 0));
		_neighborsBuffer.push_back(gridPosition + glm::i32vec2(0, 1));
		_neighborsBuffer.push_back(gridPosition + glm::i32vec2(0, -1));
	}
}
