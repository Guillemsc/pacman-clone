//
// Created by guillem on 7/14/25.
//

#include "DemoEditorWindow.h"

#include "imgui.h"

namespace GEngine
{
	DemoEditorWindow::DemoEditorWindow(const std::weak_ptr<GEngineCoreApplication> &app): EditorWindow(app, "Demo")
	{
	}

	void DemoEditorWindow::Draw()
	{
		ImGui::ShowDemoWindow(&Visible);
	}

	void DemoEditorWindow::DrawWindowContent()
	{
	}
}
