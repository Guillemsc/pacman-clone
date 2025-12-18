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
		std::vector<PathPointData> &generatedPath
		)
	{
		generatedPath.clear();

		const std::shared_ptr<PathfindingNode> initialNode = std::make_shared<PathfindingNode>(
			0,
			GEngine::Vec2Extensions::Distance(originGridPosition, targetGridPosition),
			PathPointData { originGridPosition, false },
			nullptr
			);
		_checkingNodes.push(initialNode);

		std::shared_ptr<PathfindingNode> foundNode;
		bool nodeFound = false;

		while (!_checkingNodes.empty())
		{
			std::shared_ptr<PathfindingNode> currentNode = _checkingNodes.top();

			if (currentNode->pathPoint.gridPosition == targetGridPosition)
			{
				foundNode = currentNode;
				nodeFound = true;
				break;
			}

			_checkingNodes.pop();
			_checkedNodes.insert(currentNode->pathPoint.gridPosition);
			_checkedNodesByDistance.push(currentNode);

			glm::i32vec2 direction = GetDirectionFromParent(currentNode.get(), allowedDirection);
			GenerateNeighbors(currentNode->pathPoint.gridPosition, direction);

			for (const PathPointData& neighbor : _neighborsBuffer)
			{
				const bool isWalkable = _mapMovementManager->IsWalkable(neighbor.gridPosition);
				if (!isWalkable) continue;

				const bool alreadyChecked = _checkedNodes.contains(neighbor.gridPosition);
				if (alreadyChecked) continue;

				const std::shared_ptr<PathfindingNode> newNode = std::make_shared<PathfindingNode>(
					0,
					GEngine::Vec2Extensions::Distance(neighbor.gridPosition, targetGridPosition),
					neighbor,
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

		if (checkingNode->pathPoint.gridPosition == originGridPosition)
		{
			return { false, false, originGridPosition };
		}

		while (true)
		{
			generatedPath.push_back(checkingNode->pathPoint);

			if (checkingNode->pathPoint.gridPosition == originGridPosition)
			{
				break;
			}

			checkingNode = checkingNode->parent;

			if (!checkingNode)
			{
				break;
			}
		}

		std::ranges::reverse(generatedPath);

		return { true, couldReachTarget, foundNode->pathPoint.gridPosition };
	}

	void MapPathfindingManager::GenerateWalkableNeighbors(
		const glm::i32vec2 &originGridPosition,
		const glm::i32vec2 &allowedDirection,
		std::vector<PathPointData> &generatedNeighbors
		)
	{
		generatedNeighbors.clear();

		GenerateNeighbors(originGridPosition, allowedDirection);

		for (const PathPointData& neighbor : _neighborsBuffer)
		{
			const bool isWalkable = _mapMovementManager->IsWalkable(neighbor.gridPosition);
			if (!isWalkable) continue;

			generatedNeighbors.push_back(neighbor);
		}
	}

	glm::i32vec2 MapPathfindingManager::GetDirectionFromParent(const PathfindingNode *pathfindingNode, const glm::i32vec2& defaultDirection)
	{
		if (!pathfindingNode->parent) return defaultDirection;

		if (pathfindingNode->parent->pathPoint.fromPortal)
		{
			const std::optional<MapPortalData> portalData = _mapMovementManager->GetPortal(pathfindingNode->pathPoint.gridPosition);

			if (portalData.has_value())
			{
				return portalData.value().exitDirection;
			}
		}

		return pathfindingNode->pathPoint.gridPosition - pathfindingNode->parent->pathPoint.gridPosition;
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

			const glm::i32vec2 finalGridPosition = gridPosition + direction;
			_neighborsBuffer.push_back({ finalGridPosition, false });
		}

		const auto optionalPortal = _mapMovementManager->GetPortal(gridPosition);

		if (optionalPortal.has_value())
		{
			const MapPortalData portalData = optionalPortal.value();
			const MapPortalData connectedPortalData = _mapMovementManager->GetPortal(portalData.connectedPortalId).value();
			_neighborsBuffer.push_back({ connectedPortalData.gridPosition, true });
		}
	}
}
