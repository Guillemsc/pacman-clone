//
// Created by guillem on 6/9/25.
//

#include "EditorWindow.h"

#include "imgui.h"

namespace GEngine
{
	EditorWindow::EditorWindow(const std::weak_ptr<GEngineCoreApplication> &app, const std::string& windowTitle)
	{
		_app = app;
		_title = windowTitle;
	}

	void EditorWindow::Draw()
	{
		if (ImGui::Begin(_title.c_str(), &Visible))
		{
			DrawWindowContent();

			ImGui::End();
		}
	}

	std::string EditorWindow::GetTitle() const
	{
		return _title;
	}
} // GEngineCore