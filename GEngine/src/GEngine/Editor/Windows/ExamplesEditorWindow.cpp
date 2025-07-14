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
	ExamplesEditorWindow::ExamplesEditorWindow(const std::weak_ptr<GEngineCoreApplication> &app)
		: EditorWindow(app, "Examples")
	{
	}

	void ExamplesEditorWindow::DrawWindowContent()
	{
		const std::shared_ptr<GEngineCoreApplication> app = _app.lock();
		if (!app) return;

		const std::shared_ptr<ExamplesModule> examples = app->Examples().lock();
		if (!examples) return;

		const std::shared_ptr<GameModule> game = app->Game().lock();
		if (!game) return;

		const std::vector<ExampleData>& examplesList = examples->GetExamples();

		for (auto it = examplesList.begin(); it != examplesList.end(); ++it)
		{
			ImGui::PushID(it->name.c_str());

			if (ImGui::Button("Run"))
			{
				game->LoadGame(it->example);
			}

			ImGui::SameLine();
			ImGui::Text(it->name.c_str());

			ImGui::PopID();
		}
	}
}
