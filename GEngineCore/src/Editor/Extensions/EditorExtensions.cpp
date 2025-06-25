//
// Created by guillem on 6/25/25.
//

#include "EditorExtensions.h"

#include "imgui.h"
#include "Modules/EditorModule.h"
#include "Resources/Resource.h"

namespace GEngineCore
{
	void EditorExtensions::DrawResource(
		EditorModule* editor,
		const char *resourceName,
		const std::weak_ptr<Resource> &resourcePtr
		)
	{
		const std::shared_ptr<Resource> resource = resourcePtr.lock();

		if (!resource)
		{
			ImGui::Text("%s: none", resourceName);
		}
		else
		{
			ImGui::Text("%s: %s", resourceName, resource->GetResourcesPath().c_str());

			ImGui::SameLine();

			if (ImGui::Button("Find"))
			{
				editor->SetSelectedObject(resource);
			}
		}
	}
} // GEngineCore