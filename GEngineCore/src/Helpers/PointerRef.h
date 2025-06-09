//
// Created by guillem on 6/7/25.
//

#ifndef POINTERREF_H
#define POINTERREF_H

#include <cstdint>

namespace GEngineCore
{
	struct PointerRef
	{
		PointerRef(const std::uint32_t index, const std::uint32_t generation)
			: index(index), generation(generation) {}

		std::uint32_t index = -1;
		std::uint32_t generation = 0;

		bool operator==(const PointerRef& other) const
		{
			return index == other.index && generation == other.generation;
		}

		bool operator!=(const PointerRef& other) const
		{
			return !(*this == other);
		}
	};
}

#endif //POINTERREF_H
