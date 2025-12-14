//
// Created by guillem on 12/2/25.
//

#include "GuizmosEditorWindow.h"

#include "imgui.h"
#include "GEngine/ComponentsRegister/ComponentsRegister.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Modules/GuizmosModule.h"

namespace GEngine
{
	GuizmosEditorWindow::GuizmosEditorWindow(GEngineCoreModules *modules)
		: EditorWindow(modules, "Guizmos")
	{
	}

	void GuizmosEditorWindow::DrawWindowContent()
	{
		for (const std::string_view& componentName : ComponentsRegister::GetComponentRegistry())
		{
			bool isEnabled = _modules->guizmos->IsComponentEnabled(componentName);
			if (ImGui::Checkbox(componentName.data(), &isEnabled))
			{
				_modules->guizmos->SetComponentEnabled(componentName, isEnabled);
			}
		}
	}
}
