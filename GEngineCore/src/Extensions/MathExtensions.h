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

		static float SafeDivide(const float v1, const float v2)
		{
			if (v2 == 0.0f)
			{
				return 0.0f;
			}

			return v1 / v2;
		}

		static float IntSafeDivide(const int v1, const int v2)
		{
			if (v2 == 0)
			{
				return 0.0f;
			}

			return v1 / v2;
		}
	};
}

#endif //MATHEXTENSIONS_H
