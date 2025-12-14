//
// Created by guillem on 12/2/25.
//

#ifndef COMPONENTSREGISTER_H
#define COMPONENTSREGISTER_H

#include <string>
#include <vector>

namespace GEngine
{
	struct ComponentsRegister
	{
		explicit ComponentsRegister(const std::string_view& name)
		{
			GetComponentRegistry().push_back(name);
		}

		static std::vector<std::string_view>& GetComponentRegistry()
		{
			static std::vector<std::string_view> registry;
			return registry;
		}
	};
}

#endif //COMPONENTSREGISTER_H
