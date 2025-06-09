//
// Created by guillem on 6/9/25.
//

#include "EditorModule.h"

#include "imgui.h"
#include "RenderingModule.h"
#include "Core/GEngineCoreApplication.h"
#include "Editor/Windows/EditorWindow.h"
#include "Editor/Windows/HierarchyEditorWindow.h"
#include "Editor/Windows/InspectorEditorWindow.h"
#include "Editor/Windows/ResourcesEditorWindow.h"
#include "Rendering/ImGuiRenderer.h"

namespace GEngineCore
{
	void EditorModule::Init(const std::weak_ptr<GEngineCoreApplication> &app)
	{
		_app = app;

		RegisterWindow<HierarchyEditorWindow>();
		RegisterWindow<InspectorEditorWindow>();
		RegisterWindow<ResourcesEditorWindow>();
	}

	void EditorModule::Tick()
	{
		DrawEditor();
	}

	void EditorModule::Dispose()
	{
	}

	void EditorModule::SetSelectedObject(const std::weak_ptr<GEngineObject> &object)
	{
		_selectedObject = object;
	}

	std::weak_ptr<GEngineObject> EditorModule::GetSelectedObject() const
	{
		return _selectedObject;
	}

	void EditorModule::DrawEditor()
	{
		const std::shared_ptr<GEngineCoreApplication> app = _app.lock();
		if (app == nullptr) return;

		const std::shared_ptr<RenderingModule> rendering = app->Rendering().lock();
		if (rendering == nullptr) return;

		const std::shared_ptr<ImGuiRenderer> imGuiRenderer = rendering->ImGuiRender().lock();
		if (imGuiRenderer == nullptr) return;

		imGuiRenderer->Add([this]()
		{
			bool open = true;
			ImGui::ShowDemoWindow(&open);

			DrawWindows();
		});
	}

	void EditorModule::DrawWindows()
	{
		for (auto it = _windows.begin(); it != _windows.end(); ++it)
		{
			if (!(*it)->visible)
			{
				continue;
			}

			(*it)->Draw();
		}
	}
} // GEngineCore