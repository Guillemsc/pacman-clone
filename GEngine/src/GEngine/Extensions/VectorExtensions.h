//
// Created by guillem on 6/7/25.
//

#ifndef VECTOREXTENSIONS_H
#define VECTOREXTENSIONS_H

#include <algorithm>
#include <vector>

namespace GEngine
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
		static void Remove(std::vector<std::shared_ptr<T>>& vec, const std::weak_ptr<T>& valuePtr)
		{
			const std::shared_ptr<T> value = valuePtr.lock();
			if (!value) return;

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

		template <typename T>
		static bool IsIndexOutsideBounds(const std::vector<T>& vec, const std::int32_t index)
		{
			return index < 0 || vec.size() <= index;
		}

		template <typename T>
		static T GetOrDefault(const std::vector<T>& vec, const std::int32_t index, T defaultValue)
		{
			if (IsIndexOutsideBounds(vec, index))
			{
				return defaultValue;
			}

			return vec[index];
		}

		template <typename T>
		static const T& GetOrDefaultRef(const std::vector<T>& vec, const std::int32_t index, const T& defaultValue)
		{
			if (IsIndexOutsideBounds(vec, index))
			{
				return defaultValue;
			}

			return vec[index];
		}

		template <typename T>
		static void EraseOrIncrease(
			std::vector<T>& vec,
			std::vector<T>::iterator& it,
			const bool remove
			)
		{
			if (remove)
			{
				it = vec.erase(it);
			}
			else
			{
				++it;
			}
		}

		template <typename T>
		static void RemoveAt(
			std::vector<T>& vec,
			int index
			)
		{
			if (index < 0 || index >= vec.size()) return;

			vec.erase(vec.begin() + index);
		}
	};
} // GEngineCore

#endif //VECTOREXTENSIONS_H
