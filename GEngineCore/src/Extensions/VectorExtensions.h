//
// Created by guillem on 6/7/25.
//

#ifndef VECTOREXTENSIONS_H
#define VECTOREXTENSIONS_H

#include <algorithm>
#include <vector>

namespace GEngineCore
{
	class VectorExtensions
	{
	public:
		template <typename T>
		static void Remove(std::vector<std::shared_ptr<T>>& vec, const std::shared_ptr<T>& value)
		{
			vec.erase(
				std::remove_if(
					vec.begin(),
					vec.end(),
					[&value](const std::shared_ptr<T>& elem)
					{
						return elem.get() == value.get();
					}
				),
			vec.end()
			);
		}

		template <typename T>
		static void Remove(std::vector<std::weak_ptr<T>>& vec, const std::shared_ptr<T>& value)
		{
			vec.erase(
				std::remove_if(
					vec.begin(),
					vec.end(),
					[&value](const std::weak_ptr<T>& elem)
					{
						return !elem.owner_before(value) && !value.owner_before(elem);
					}
				),
				vec.end()
			);
		}
	};
} // GEngineCore

#endif //VECTOREXTENSIONS_H
