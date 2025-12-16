//
// Created by guillem on 6/25/25.
//

#ifndef VEC2EXTENSIONS_H
#define VEC2EXTENSIONS_H

#include "glm/vec2.hpp"
#include "GEngine/Extensions/MathExtensions.h"
#include "glm/ext/quaternion_geometric.hpp"

namespace GEngine
{
	class Vec2Extensions
	{
	public:
		constexpr static glm::vec2 Zero = glm::vec2(0);
		constexpr static glm::vec2 One = glm::vec2(1);

		constexpr static glm::i32vec2 Int32Zero = glm::i32vec2(0);
		constexpr static glm::i32vec2 Int32One = glm::i32vec2(1);

		static glm::vec2 SafeDivide(const glm::vec2 v1, const glm::vec2 v2)
		{
			return { MathExtensions::SafeDivide(v1.x, v2.x), MathExtensions::SafeDivide(v1.y, v2.y) };
		}

		static glm::vec2 GetNormalizedValue(const glm::vec2 value, const glm::vec2 start, const glm::vec2 end)
		{
			return {
				MathExtensions::GetNormalizedValue(value.x, start.x, end.x),
				MathExtensions::GetNormalizedValue(value.y, start.y, end.y)
			};
		}

		static glm::vec2 Lerp(const glm::vec2 v1, const glm::vec2 v2, const float time)
		{
			return glm::vec2(
				MathExtensions::Lerp(v1.x, v2.x, time),
				MathExtensions::Lerp(v1.y, v2.y, time)
			);
		}

		static glm::vec2 Lerp(const glm::vec2 v1, const glm::vec2 v2, const glm::vec2& time)
		{
			return glm::vec2(
				MathExtensions::Lerp(v1.x, v2.x, time.x),
				MathExtensions::Lerp(v1.y, v2.y, time.y)
			);
		}

		static float Distance(const glm::i32vec2 v1, const glm::i32vec2 v2)
		{
			const glm::i32vec2 delta = v2 - v1;
			return std::sqrt(delta.x * delta.x + delta.y * delta.y);
		}

		static glm::vec2 SafeNormalize(const glm::vec2& v)
		{
			if (v == Zero) return Zero;
			return glm::normalize(v);
		}

		static glm::i32vec2 Normalize(const glm::i32vec2& v)
		{
			glm::i32vec2 ret = glm::i32vec2(0);

			if (v.x > 0)
			{
				ret.x = 1;
			}
			else if (v.x < 0)
			{
				ret.x = -1;
			}

			if (v.y > 0)
			{
				ret.y = 1;
			}
			else if (v.y < 0)
			{
				ret.y = -1;
			}

			return ret;
		}
	};
}

#endif //VEC2EXTENSIONS_H
