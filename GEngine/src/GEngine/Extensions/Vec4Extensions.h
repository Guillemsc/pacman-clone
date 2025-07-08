//
// Created by guillem on 7/1/25.
//

#ifndef VEC4EXTENSIONS_H
#define VEC4EXTENSIONS_H

#include "MathExtensions.h"
#include "glm/vec4.hpp"
#include "glm/vec2.hpp"

namespace GEngine
{
	class Vec4Extensions
	{
	public:
		constexpr static glm::vec4 Zero = glm::vec4(0);

		static glm::vec2 GetSize(const glm::vec4& value)
		{
			return { value.z - value.x, value.w - value.y };
		}

		static glm::vec2 GetCenter(const glm::vec4& value)
		{
			return { (value.x + value.z) * 0.5f, (value.y + value.w) * 0.5f };
		}

		static glm::vec2 GetMin(const glm::vec4& value)
		{
			return { value.x, value.y };
		}

		static glm::vec2 GetMax(const glm::vec4& value)
		{
			return { value.z, value.w };
		}

		static glm::vec4 FromMinMax(const glm::vec2& min, const glm::vec2& max)
		{
			return { min.x, min.y, max.x, max.y };
		}

		static bool Contains(const glm::vec4& value, const glm::vec2& check)
		{
			return check.x >= value.x && check.y >= value.y && check.x <= value.z && check.y <= value.w;
		}

		static glm::vec4 RotateAroundPivot(const glm::vec4& value, const glm::vec2& pivot, const float radians)
		{
			glm::vec2 min = GetMin(value);
			glm::vec2 max = GetMax(value);

			min = MathExtensions::RotatePointAroundPivot(min, pivot, radians);
			max = MathExtensions::RotatePointAroundPivot(max, pivot, radians);

			return { min.x, min.y, max.x, max.y };
		}
	};
}

#endif //VEC4EXTENSIONS_H
