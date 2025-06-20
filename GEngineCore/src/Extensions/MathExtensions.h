//
// Created by guillem on 6/20/25.
//

#ifndef MATHEXTENSIONS_H
#define MATHEXTENSIONS_H

#include <cmath>

#include "glm/vec2.hpp"

namespace GEngineCore
{
	class MathExtensions
	{
	public:
		static glm::vec2 RotatePointAroundPivot(const glm::vec2 point, const glm::vec2 pivot, const float radians)
		{
			const glm::vec2 pivotOffset = point - pivot;

			float rotatedX = pivot.x + (pivotOffset.x * std::cos(radians)) - (pivotOffset.y * std::sin(radians));
			float rotatedY = pivot.y + (pivotOffset.x * std::sin(radians)) + (pivotOffset.y * std::cos(radians));

			return { rotatedX, rotatedY };
		}
	};
}

#endif //MATHEXTENSIONS_H
