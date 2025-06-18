//
// Created by guillem on 6/9/25.
//

#include "ResourcesEditorWindow.h"

#include <format>
#include <vector>

#include "imgui.h"
#include "Core/GEngineCoreApplication.h"
#include "Modules/EditorModule.h"
#include "Modules/ResourcesModule.h"
#include "Resources/Resource.h"

namespace GEngineCore
{
	ResourcesEditorWindow::ResourcesEditorWindow(const std::weak_ptr<GEngineCoreApplication>& app): EditorWindow(app)
	{
	}

	void ResourcesEditorWindow::Draw()
	{
		const std::shared_ptr<GEngineCoreApplication> app = _app.lock();
		if (!app) return;

		const std::shared_ptr<ResourcesModule> resources = app->Resources().lock();
		if (!resources) return;

		const std::shared_ptr<EditorModule> editor = app->Editor().lock();
		if (!editor) return;

		ImGui::Begin("Resources");

		const std::shared_ptr<GEngineObject> selectedObject = editor->GetSelectedObject().lock();

		const std::vector<std::shared_ptr<Resource>>& resourcesList = resources->GetResources();

		for (auto it = resourcesList.begin(); it != resourcesList.end(); ++it)
		{
			std::string displayString = std::format("{} | {}", (*it)->GetTypeName(), (*it)->GetResourcesPath().c_str());

			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;

			if (selectedObject)
			{
				const bool isSelected = it->get() == selectedObject.get();

				if (isSelected)
				{
					flags |= ImGuiTreeNodeFlags_Selected;
				}
			}

			if (ImGui::TreeNodeEx(displayString.c_str(), flags))
			{
				DrawLeftClickContextMenu(editor, *it);

				ImGui::TreePop();
			}
		}

		ImGui::End();
	}

	void ResourcesEditorWindow::DrawLeftClickContextMenu(
		const std::shared_ptr<EditorModule> &editor,
		const std::shared_ptr<Resource> &resource
		)
	{
		if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
		{
			editor->SetSelectedObject(resource);
		}
	}
} // GEngineCore