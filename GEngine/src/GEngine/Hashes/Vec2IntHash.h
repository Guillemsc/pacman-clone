//
// Created by guillem on 11/27/25.
//

#ifndef VEC2INTHASH_H
#define VEC2INTHASH_H

#include <glm/glm.hpp>

namespace GEngine
{
	struct Vec2IntHash
	{
		std::size_t operator()(const glm::i32vec2& v) const noexcept
		{
			const std::size_t h1 = std::hash<int>()(v.x);
			const std::size_t h2 = std::hash<int>()(v.y);
			return h1 ^ (h2 << 1);
		}
	};
}

#endif //VEC2INTHASH_H
