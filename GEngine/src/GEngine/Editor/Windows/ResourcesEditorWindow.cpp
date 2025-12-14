//
// Created by guillem on 6/9/25.
//

#include "ResourcesEditorWindow.h"

#include <format>
#include <vector>

#include "imgui.h"
#include "GEngine/Core/GEngineCoreApplication.h"
#include "GEngine/Modules/EditorModule.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Resources/Resource.h"

namespace GEngine
{
	ResourcesEditorWindow::ResourcesEditorWindow(GEngineCoreModules* modules)
		: EditorWindow(modules, "Resources")
	{
	}

	void ResourcesEditorWindow::DrawWindowContent()
	{
		const std::shared_ptr<GEngineObject> selectedObject = _modules->editor->GetSelectedObject().lock();

		const std::vector<std::shared_ptr<Resource>>& resourcesList = _modules->resources->GetResources();

		for (auto it = resourcesList.begin(); it != resourcesList.end(); ++it)
		{
			std::string_view resourcePath = (*it)->GetResourcesPathStringView();
			_stringBuilder.Clear();
			_stringBuilder.AppendFormat("%s | %s", (*it)->GetTypeName(), resourcePath.data());

			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;

			if (selectedObject)
			{
				const bool isSelected = it->get() == selectedObject.get();

				if (isSelected)
				{
					flags |= ImGuiTreeNodeFlags_Selected;
				}
			}

			if (ImGui::TreeNodeEx(_stringBuilder.c_str(), flags))
			{
				DrawLeftClickContextMenu(_modules->editor, *it);

				ImGui::TreePop();
			}
		}
	}

	void ResourcesEditorWindow::DrawLeftClickContextMenu(
		EditorModule* editor,
		const std::shared_ptr<Resource> &resource
		)
	{
		if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
		{
			editor->SetSelectedObject(resource);
		}
	}
} // GEngineCore