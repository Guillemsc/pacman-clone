//
// Created by guillem on 6/25/25.
//

#ifndef VEC2EXTENSIONS_H
#define VEC2EXTENSIONS_H

#include "glm/vec2.hpp"
#include "GEngine/Extensions/MathExtensions.h"

namespace GEngine
{
	class Vec2Extensions
	{
	public:
		constexpr static glm::vec2 Zero = glm::vec2(0);
		constexpr static glm::i32vec2 Int32Zero = glm::i32vec2(0);

		static glm::vec2 GetNormalizedValue(const glm::vec2 value, const glm::vec2 start, const glm::vec2 end)
		{
			return {
				MathExtensions::GetNormalizedValue(value.x, start.x, end.x),
				MathExtensions::GetNormalizedValue(value.y, start.y, end.y)
			};
		}
	};
}

#endif //VEC2EXTENSIONS_H
