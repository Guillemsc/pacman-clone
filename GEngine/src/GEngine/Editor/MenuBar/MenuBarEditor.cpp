//
// Created by guillem on 6/17/25.
//

#include "MenuBarEditor.h"

#include "imgui.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Editor/Windows/EditorWindow.h"
#include "GEngine/Modules/CameraModule.h"
#include "GEngine/Modules/EditorModule.h"

namespace GEngine
{
	MenuBarEditor::MenuBarEditor(const std::weak_ptr<GEngineCoreApplication>& app)
	{
		_appPtr = app;
	}

	void MenuBarEditor::Draw()
	{
		const std::shared_ptr<GEngineCoreApplication> app = _appPtr.lock();
		if (!app) return;

		const std::shared_ptr<CameraModule> camera = app->Camera().lock();
		if (!camera) return;

		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				ImGui::EndMenu();
			}

			bool isUsingEditorCamera = camera->GetIsUsingEditorCamera();
			if (ImGui::Checkbox("Use Editor Camera", &isUsingEditorCamera))
			{
				camera->SetIsUsingEditorCamera(isUsingEditorCamera);
			}

			DrawWindows(app.get());

			ImGui::EndMainMenuBar();
		}
	}

	void MenuBarEditor::DrawWindows(GEngineCoreApplication *app)
	{
		if (ImGui::BeginMenu("Windows"))
		{
			const std::shared_ptr<EditorModule> editor = app->Editor().lock();
			std::vector<std::shared_ptr<EditorWindow>> windows =editor->GetEditorWindows();

			for (auto it = windows.begin(); it != windows.end(); ++it)
			{
				ImGui::Checkbox(it->get()->GetTitle().c_str(), &it->get()->Visible);
			}

			ImGui::EndMenu();
		}
	}
} // GEngineCore