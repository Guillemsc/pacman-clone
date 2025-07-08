//
// Created by guillem on 7/8/25.
//

#include "UiRect.h"

#include <cmath>

#include "GEngine/Extensions/Vec4Extensions.h"

namespace GEngine
{
	UiRect UiRect::Transform(const UiRect &parent, const UiRect &child)
	{
		const glm::vec2 scaledLocalPos = child.position * parent.scale;

		const float sin = std::sin(-parent.rotation);
		const float cos = std::cos(-parent.rotation);

		const glm::vec2 rotatedLocalPos = {
			scaledLocalPos.x * cos - scaledLocalPos.y * sin,
			scaledLocalPos.x * sin + scaledLocalPos.y * cos
		};

		// Step 2: Compose transforms
		UiRect global;
		global.position = parent.position + rotatedLocalPos;
		global.rotation = parent.rotation + child.rotation;
		global.scale = parent.scale * child.scale;
		global.size = child.size * global.scale;

		return global;
	}

	glm::vec2 UiRect::GetPointFromNormalizedPoint(const glm::vec2& point) const
	{
		glm::vec2 finalPoint = (point - glm::vec2(0.5f)) * size;

		finalPoint *= scale;

		const float sin = std::sin(-rotation);
		const float cos = std::cos(-rotation);

		const glm::vec2 rotated = {
			finalPoint.x * cos - finalPoint.y * sin,
			finalPoint.x * sin + finalPoint.y * cos
		};

		finalPoint = position + rotated;

		return finalPoint;
	}

	glm::vec4 UiRect::GetRectFromNormalizedRect(const glm::vec4 &point) const
	{
		const glm::vec2 min = Vec4Extensions::GetMin(point);
		const glm::vec2 max = Vec4Extensions::GetMax(point);

		const glm::vec2 minFinal = GetPointFromNormalizedPoint(min);
		const glm::vec2 maxFinal = GetPointFromNormalizedPoint(max);

		return Vec4Extensions::FromMinMax(minFinal, maxFinal);
	}
} // GEngine