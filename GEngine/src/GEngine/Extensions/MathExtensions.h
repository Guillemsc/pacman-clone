//
// Created by guillem on 6/20/25.
//

#ifndef MATHEXTENSIONS_H
#define MATHEXTENSIONS_H

#include <cmath>

#include "glm/vec2.hpp"

namespace GEngine
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

		static glm::vec2 InverseRotatePointAroundPivot(const glm::vec2 point, const glm::vec2 pivot, const float radians)
		{
			return RotatePointAroundPivot(point, pivot, -radians);
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

		static float GetNormalizedValue(const float value, const float start, const float end)
		{
			return SafeDivide(value - start, end - start);
		}
	};
}

#endif //MATHEXTENSIONS_H
