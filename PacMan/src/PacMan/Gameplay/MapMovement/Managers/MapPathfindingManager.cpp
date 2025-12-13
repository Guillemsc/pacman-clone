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

	PathfindingResult MapPathfindingManager::GeneratePath(
		const glm::i32vec2 &originGridPosition,
		const glm::i32vec2 &allowedDirection,
		const glm::i32vec2 &targetGridPosition,
		std::vector<glm::i32vec2> &generatedPath
		)
	{
		generatedPath.clear();

		const std::shared_ptr<PathfindingNode> initialNode = std::make_shared<PathfindingNode>(
			0,
			GEngine::Vec2Extensions::Distance(originGridPosition, targetGridPosition),
			originGridPosition,
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
			_checkedNodesByDistance.push(currentNode);

			glm::i32vec2 direction = GetDirectionFromParent(currentNode.get(), allowedDirection);
			GenerateNeighbors(currentNode->position, direction);

			for (glm::i32vec2 neighborGridPosition : _neighborsBuffer)
			{
				const bool isWalkable = _mapMovementManager->IsWalkable(neighborGridPosition);
				if (!isWalkable) continue;

				const bool alreadyChecked = _checkedNodes.contains(neighborGridPosition);
				if (alreadyChecked) continue;

				const std::shared_ptr<PathfindingNode> newNode = std::make_shared<PathfindingNode>(
					0,
					GEngine::Vec2Extensions::Distance(neighborGridPosition, targetGridPosition),
					neighborGridPosition,
					currentNode
					);
				_checkingNodes.push(newNode);
			}
		}

		_checkingNodes = std::priority_queue<std::shared_ptr<PathfindingNode>, std::vector<std::shared_ptr<PathfindingNode>>, PathfindingComparer>();
		_checkedNodes.clear();

		bool couldReachTarget = true;

		if (!nodeFound)
		{
			if (_checkedNodesByDistance.empty()) return { false, false, originGridPosition };

			foundNode = _checkedNodesByDistance.top();
			couldReachTarget = false;
		}

		_checkedNodesByDistance = std::priority_queue<std::shared_ptr<PathfindingNode>, std::vector<std::shared_ptr<PathfindingNode>>, PathfindingComparer>();

		std::shared_ptr<PathfindingNode> checkingNode = foundNode;

		if (checkingNode->position == originGridPosition)
		{
			return { false, false, originGridPosition };
		}

		while (true)
		{
			if (checkingNode->position == originGridPosition)
			{
				break;
			}

			generatedPath.push_back(checkingNode->position);

			checkingNode = checkingNode->parent;

			if (!checkingNode)
			{
				break;
			}
		}

		std::ranges::reverse(generatedPath);

		return { true, couldReachTarget, foundNode->position };
	}

	void MapPathfindingManager::GenerateWalkableNeighbors(
		const glm::i32vec2 &originGridPosition,
		const glm::i32vec2 &allowedDirection,
		std::vector<glm::i32vec2> &generatedNeighbors
		)
	{
		generatedNeighbors.clear();

		GenerateNeighbors(originGridPosition, allowedDirection);

		for (glm::i32vec2 neighbor : _neighborsBuffer)
		{
			const bool isWalkable = _mapMovementManager->IsWalkable(neighbor);
			if (!isWalkable) continue;

			generatedNeighbors.push_back(neighbor);
		}
	}

	glm::i32vec2 MapPathfindingManager::GetDirectionFromParent(const PathfindingNode *pathfindingNode, const glm::i32vec2& defaultDirection)
	{
		if (!pathfindingNode->parent) return defaultDirection;

		return pathfindingNode->position - pathfindingNode->parent->position;
	}

	void MapPathfindingManager::GenerateNeighbors(
		const glm::i32vec2 &gridPosition,
		const glm::i32vec2 &allowedDirection
		)
	{
		static constexpr glm::i32vec2 directions[4] = {
			{ 1,  0},
			{-1,  0},
			{ 0,  1},
			{ 0, -1}
		};

		const glm::i32vec2 reverseDirection = -allowedDirection;

		_neighborsBuffer.clear();

		for (const glm::i32vec2& direction : directions)
		{
			const bool isReverseDirection = reverseDirection == direction;

			if (isReverseDirection) continue;

			_neighborsBuffer.push_back(gridPosition + direction);
		}
	}
}
