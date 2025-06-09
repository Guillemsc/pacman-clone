//
// Created by guillem on 6/7/25.
//

#ifndef MAPEXTENSIONS_H
#define MAPEXTENSIONS_H

#include <map>
#include <optional>

namespace GEngineCore
{
	class MapExtensions
	{
	public:
		template <typename TKey, typename TValue>
		static std::optional<TValue> GetValue(const std::map<TKey, TValue>& map, TKey key)
		{
			auto foundIterator = map.find(key);

			if (foundIterator == map.end())
			{
				return std::nullopt;
			}

			return (*foundIterator).second;
		}
	};
} // GEngineCore

#endif //MAPEXTENSIONS_H
