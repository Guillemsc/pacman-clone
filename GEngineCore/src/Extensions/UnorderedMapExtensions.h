//
// Created by guillem on 6/7/25.
//

#ifndef UNORDEREDMAPEXTENSIONS_H
#define UNORDEREDMAPEXTENSIONS_H

#include <optional>
#include <unordered_map>

namespace GEngineCore
{
	class UnorderedMapExtensions
	{
	public:
		template <typename TKey, typename TValue>
		static std::optional<TValue> GetValue(const std::unordered_map<TKey, TValue>& map, const TKey& key)
		{
			auto foundIterator = map.find(key);

			if (foundIterator == map.end())
			{
				return std::nullopt;
			}

			return (*foundIterator).second;
		}

		template <typename TKey, typename TValue>
		static bool RemoveKey(std::unordered_map<TKey, TValue>& map, const TKey& key)
		{
			auto foundIterator = map.find(key);

			if (foundIterator == map.end())
			{
				return false;
			}

			map.erase(foundIterator);

			return true;
		}
	};
}

#endif //UNORDEREDMAPEXTENSIONS_H
