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
	UiEditorWindow::UiEditorWindow(GEngineCoreModules* modules): EditorWindow(modules, "Ui")
	{
	}

	void UiEditorWindow::DrawWindowContent()
	{
		glm::vec2 referenceScreenSize = _modules->ui->GetReferenceScreenSize();
		if (ImGui::DragFloat2("Reference Screen Size", &referenceScreenSize.x, 1))
		{
			_modules->ui->SetReferenceScreenSize(referenceScreenSize);
		}

		ImGui::Text("%s", std::format("Scale: {:.2f}", _modules->ui->GetUiScale()).c_str());
	}
}
