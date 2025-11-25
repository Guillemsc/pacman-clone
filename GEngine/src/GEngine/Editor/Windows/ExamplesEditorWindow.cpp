//
// Created by guillem on 7/12/25.
//

#include "ExamplesEditorWindow.h"

#include "imgui.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Data/ExampleData.h"
#include "GEngine/Modules/ExamplesModule.h"
#include "GEngine/Modules/GameModule.h"

namespace GEngine
{
	ExamplesEditorWindow::ExamplesEditorWindow(GEngineCoreModules* modules)
		: EditorWindow(modules, "Examples")
	{
	}

	void ExamplesEditorWindow::DrawWindowContent()
	{
		const std::vector<ExampleData>& examplesList = _modules->examples->GetExamples();

		for (auto it = examplesList.begin(); it != examplesList.end(); ++it)
		{
			ImGui::PushID(it->name.c_str());

			if (ImGui::Button("Run"))
			{
				_modules->game->LoadGame(it->example);
			}

			ImGui::SameLine();
			ImGui::Text(it->name.c_str());

			ImGui::PopID();
		}
	}
}
