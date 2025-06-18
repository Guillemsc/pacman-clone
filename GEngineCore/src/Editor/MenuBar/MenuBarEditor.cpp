//
// Created by guillem on 6/17/25.
//

#include "MenuBarEditor.h"

#include "imgui.h"
#include "Core/GEngineCoreApplication.h"
#include "Modules/CameraModule.h"

namespace GEngineCore
{
	MenuBarEditor::MenuBarEditor(const std::weak_ptr<GEngineCoreApplication>& app)
	{
		_app = app;
	}

	void MenuBarEditor::Draw()
	{
		const std::shared_ptr<GEngineCoreApplication> app = _app.lock();
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

			ImGui::EndMainMenuBar();
		}
	}
} // GEngineCore