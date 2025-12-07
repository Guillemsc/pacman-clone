//
// Created by guillem on 6/17/25.
//

#include "MenuBarEditor.h"

#include "imgui.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Editor/Windows/EditorWindow.h"
#include "GEngine/Modules/CameraModule.h"
#include "GEngine/Modules/EditorModule.h"
#include "GEngine/Modules/TimeModule.h"

namespace GEngine
{
	MenuBarEditor::MenuBarEditor(GEngineCoreModules* modules)
		: _modules(modules)
	{

	}

	void MenuBarEditor::Draw() const
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Menu"))
			{
				ImGui::EndMenu();
			}

			bool isUsingEditorCamera = _modules->camera->GetIsUsingEditorCamera();
			if (ImGui::Checkbox("Use Editor Camera", &isUsingEditorCamera))
			{
				_modules->camera->SetIsUsingEditorCamera(isUsingEditorCamera);
			}

			DrawWindows();

			const int fps = _modules->time->GetFps();
			ImGui::Text("%d", fps);

			ImGui::EndMainMenuBar();
		}
	}

	void MenuBarEditor::DrawWindows() const
	{
		if (ImGui::BeginMenu("Windows"))
		{
			std::vector<std::shared_ptr<EditorWindow>> windows = _modules->editor->GetEditorWindows();

			for (auto it = windows.begin(); it != windows.end(); ++it)
			{
				ImGui::Checkbox(it->get()->GetTitle().c_str(), &it->get()->Visible);
			}

			ImGui::EndMenu();
		}
	}
} // GEngineCore