//
// Created by guillem on 7/1/25.
//

#ifndef VEC4EXTENSIONS_H
#define VEC4EXTENSIONS_H

#include "glm/vec4.hpp"
#include "glm/vec2.hpp"

namespace GEngine
{
	class Vec4Extensions
	{
	public:
		constexpr static glm::vec4 Zero = glm::vec4(0);

		static glm::vec2 GetSize(const glm::vec4 value)
		{
			return { value.z - value.x, value.w - value.y };
		}

		static glm::vec2 GetCenter(const glm::vec4 value)
		{
			return { (value.x + value.z) * 0.5f, (value.y + value.w) * 0.5f };
		}
	};
}

#endif //VEC4EXTENSIONS_H
