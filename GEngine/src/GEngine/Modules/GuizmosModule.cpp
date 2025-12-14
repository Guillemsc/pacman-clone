//
// Created by guillem on 12/2/25.
//

#include "GuizmosModule.h"

#include "EditorModule.h"
#include "GEngine/Components/Component.h"
#include "GEngine/Core/GEngineCoreModules.h"

namespace GEngine
{
	GuizmosModule::GuizmosModule()
	{
	}

	void GuizmosModule::Init(GEngineCoreModules *modules)
	{
		_modules = modules;
	}

	bool GuizmosModule::IsComponentEnabled(const Component *component) const
	{
		const std::string_view& name = component->GetTypeName();
		return _enabledComponents.contains(name);
	}

	bool GuizmosModule::IsComponentEnabled(const std::string_view &componentName) const
	{
		return _enabledComponents.contains(componentName);
	}

	void GuizmosModule::SetComponentEnabled(const std::string_view &componentName, const bool enabled)
	{
		if (enabled)
		{
			_enabledComponents.insert(componentName);
		}
		else
		{
			_enabledComponents.erase(componentName);
		}
	}

	void GuizmosModule::DrawComponentGuizmo(Component *component) const
	{
		const bool isEditorEnabled = _modules->editor->IsEditorEnabled();
		if (!isEditorEnabled) return;

		const bool isEnabled = IsComponentEnabled(component);
		if (!isEnabled) return;

		component->OnDrawGuizmo();
	}
}
