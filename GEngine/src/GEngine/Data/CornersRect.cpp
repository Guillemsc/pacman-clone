//
// Created by guillem on 7/11/25.
//

#include "CornersRect.h"

#include "GEngine/Extensions/Vec2Extensions.h"
#include "GEngine/Extensions/Vec4Extensions.h"
#include "glm/geometric.hpp"

namespace GEngine
{
	CornersRect CornersRect::GetFromNormalisedRect(const glm::vec4& rect) const
	{
		CornersRect finalRect;

		// Horizontal edges
		const glm::vec2 bottomLeftEdge = Vec2Extensions::Lerp(bottomLeft, bottomRight, rect.x);
		const glm::vec2 bottomRightEdge = Vec2Extensions::Lerp(bottomLeft, bottomRight, rect.z);

		// Vertical edges
		const glm::vec2 topLeftEdge = Vec2Extensions::Lerp(topLeft, topRight, rect.x);
		const glm::vec2 topRightEdge = Vec2Extensions::Lerp(topLeft, topRight, rect.z);

		// Bottom-left
		finalRect.bottomLeft.x = MathExtensions::Lerp(bottomLeftEdge.x, topLeftEdge.x, rect.y);
		finalRect.bottomLeft.y = MathExtensions::Lerp(bottomLeftEdge.y, topLeftEdge.y, rect.y);

		// Top-left
		finalRect.topLeft.x = MathExtensions::Lerp(bottomLeftEdge.x, topLeftEdge.x, rect.w);
		finalRect.topLeft.y = MathExtensions::Lerp(bottomLeftEdge.y, topLeftEdge.y, rect.w);

		// Top-right
		finalRect.topRight.x = MathExtensions::Lerp(bottomRightEdge.x, topRightEdge.x, rect.w);
		finalRect.topRight.y = MathExtensions::Lerp(bottomRightEdge.y, topRightEdge.y, rect.w);

		// Bottom-right
		finalRect.bottomRight.x = MathExtensions::Lerp(bottomRightEdge.x, topRightEdge.x, rect.y);
		finalRect.bottomRight.y = MathExtensions::Lerp(bottomRightEdge.y, topRightEdge.y, rect.y);

		return finalRect;
	}

	glm::vec2 CornersRect::GetCenter() const
	{
		return (topLeft + topRight + bottomRight + bottomLeft) * 0.25f;
	}

	glm::vec2 CornersRect::GetSize() const
	{
		const glm::vec2 widthVector  = topRight - topLeft;
		const glm::vec2 heightVector = bottomLeft - topLeft;

		const float width  = glm::length(widthVector);
		const float height = glm::length(heightVector);

		return glm::vec2(width, height);
	}
}
