//
// Created by guillem on 7/14/25.
//

#include "DemoEditorWindow.h"

#include "imgui.h"

namespace GEngine
{
	DemoEditorWindow::DemoEditorWindow(GEngineCoreModules* modules)
		: EditorWindow(modules, "Demo")
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
