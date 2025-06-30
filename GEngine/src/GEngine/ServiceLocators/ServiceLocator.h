//
// Created by guillem on 6/30/25.
//

#ifndef SERVICELOCATOR_H
#define SERVICELOCATOR_H

#include <memory>
#include <typeindex>
#include <unordered_map>

namespace GEngine
{
	class ServiceLocator
	{
	public:
		template<typename T>
		static void Register(std::shared_ptr<T> service);

		template<typename T>
		static std::shared_ptr<T> Get();

		static void Clear()
		{
			services().clear();
		}

	private:
		static std::unordered_map<std::type_index, std::shared_ptr<void>>& services()
		{
			static std::unordered_map<std::type_index, std::shared_ptr<void>> instance;
			return instance;
		}
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<typename T>
	void ServiceLocator::Register(std::shared_ptr<T> service)
	{
		const std::type_index typeIndex = std::type_index(typeid(T));
		services()[typeIndex] = service;
	}

	template<typename T>
	std::shared_ptr<T> ServiceLocator::Get()
	{
		const std::type_index typeIndex = std::type_index(typeid(T));

		const auto it = services().find(typeIndex);

		if (it != services().end())
		{
			return std::static_pointer_cast<T>(it->second);
		}

		return nullptr;
	}
}

#endif //SERVICELOCATOR_H
