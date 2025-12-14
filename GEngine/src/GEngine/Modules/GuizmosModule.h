//
// Created by guillem on 12/2/25.
//

#ifndef GUIZMOSMODULE_H
#define GUIZMOSMODULE_H

#include <memory>
#include <string>
#include <unordered_set>

namespace GEngine
{
	class GEngineCoreModules;
	class Component;

	class GuizmosModule
	{
	public:
		GuizmosModule();

		void Init(GEngineCoreModules* modules);

		bool IsComponentEnabled(const Component* component) const;
		bool IsComponentEnabled(const std::string_view& componentName) const;
		void SetComponentEnabled(const std::string_view& componentName, bool enabled);
		void DrawComponentGuizmo(Component* component) const;

	private:
		GEngineCoreModules* _modules = nullptr;

		std::unordered_set<std::string_view> _enabledComponents;
	};
}

#endif //GUIZMOSMODULE_H
