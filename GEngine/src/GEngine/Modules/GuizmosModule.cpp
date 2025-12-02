//
// Created by guillem on 12/2/25.
//

#include "GuizmosModule.h"

#include "GEngine/Components/Component.h"

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
		const std::string name = component->GetTypeName();
		return _enabledComponents.contains(name);
	}
}
