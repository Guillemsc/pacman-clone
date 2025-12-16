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
			const glm::vec2 pointInLocalSpace = point - pivot;
			const glm::vec2 rotated = RotatePointAroundOrigin(pointInLocalSpace, radians);
			const glm::vec2 pointInWorldSpace = rotated + pivot;

			return pointInWorldSpace;
		}

		static glm::vec2 RotatePointAroundOrigin(const glm::vec2 point, const float radians)
		{
			const float sin = std::sin(radians);
			const float cos = std::cos(radians);

			return RotatePointAroundOrigin(point, cos, sin);
		}

		static glm::vec2 RotatePointAroundOrigin(const glm::vec2 point, const float cos, const float sin)
		{
			float rotatedX = (point.x * cos) - (point.y * sin);
			float rotatedY = (point.x * sin) + (point.y * cos);

			return { rotatedX, rotatedY };
		}

		static glm::vec2 InverseRotatePointAroundPivot(const glm::vec2 point, const glm::vec2 pivot, const float radians)
		{
			return RotatePointAroundPivot(point, pivot, radians);
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

		static float GetNormalizedValue(const float value, const float max)
		{
			return GetNormalizedValue(value, 0.0f, max);
		}

		template <typename T>
		static T Lerp(const T& start, const T& end, float normalizedTime)
		{
			return start * (1.0f - normalizedTime) + end * normalizedTime;
		}
	};
}

#endif //MATHEXTENSIONS_H
