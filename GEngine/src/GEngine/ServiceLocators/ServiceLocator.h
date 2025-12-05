//
// Created by guillem on 6/30/25.
//

#ifndef SERVICELOCATOR_H
#define SERVICELOCATOR_H

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "GEngine/Extensions/UnorderedMapExtensions.h"

namespace GEngine
{
	class ServiceLocator
	{
	public:
		template<typename T>
		static void Register(T* service)
		{
			const std::type_index type = typeid(T);
			_services[type] = service;
		}

		template<typename T>
		static void Unregister()
		{
			const std::type_index type = typeid(T);
			UnorderedMapExtensions::RemoveKey(_services, type);
		}

		template<typename T>
		static T* Get()
		{
			const std::type_index type = typeid(T);
			const auto it = _services.find(type);
			if (it != _services.end())
			{
				return static_cast<T*>(it->second);
			}

			throw std::runtime_error(std::string("ServiceLocator: service not registered: ") + type.name());
		}

		template<typename T>
		static T* GetOrNull()
		{
			const std::type_index type = typeid(T);
			const auto it = _services.find(type);
			if (it != _services.end())
			{
				return static_cast<T*>(it->second);
			}

			return nullptr;
		}

		static void Clear()
		{
			_services.clear();
		}

	private:
		static inline std::unordered_map<std::type_index, void*> _services;
	};
}

#endif //SERVICELOCATOR_H
