//
// Created by guillem on 7/14/25.
//

#include "UiEditorWindow.h"

#include <format>

#include "imgui.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Modules/UiModule.h"

namespace GEngine
{
	UiEditorWindow::UiEditorWindow(const std::weak_ptr<GEngineCoreApplication> &app): EditorWindow(app, "Ui")
	{
	}

	void UiEditorWindow::DrawWindowContent()
	{
		const std::shared_ptr<GEngineCoreApplication> app = _app.lock();
		if (!app) return;

		const std::shared_ptr<UiModule> ui = app->Ui().lock();
		if (!ui) return;

		glm::vec2 referenceScreenSize = ui->GetReferenceScreenSize();
		if (ImGui::DragFloat2("Reference Screen Size", &referenceScreenSize.x, 1))
		{
			ui->SetReferenceScreenSize(referenceScreenSize);
		}

		ImGui::Text(std::format("Scale: {:.2f}", ui->GetUiScale()).c_str());
	}
}
