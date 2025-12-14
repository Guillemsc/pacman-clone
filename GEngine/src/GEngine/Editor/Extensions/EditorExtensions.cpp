//
// Created by guillem on 6/25/25.
//

#include "EditorExtensions.h"

#include "imgui.h"
#include "rlImGui.h"
#include "GEngine/Modules/EditorModule.h"
#include "GEngine/Resources/Resource.h"

namespace GEngine
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
			ImGui::Text("%s: %s", resourceName, resource->GetResourcesPathStringView().data());

			ImGui::SameLine();

			if (ImGui::Button("Find"))
			{
				editor->SetSelectedObject(resource);
			}
		}
	}

	void EditorExtensions::DrawRawTexture(const Texture& texture)
	{
		const float textureWidth = ImGui::GetWindowWidth() - 20;
		const float ratio = static_cast<float>(texture.height) / static_cast<float>(texture.width);
		const float textureHeight = textureWidth * ratio;
		rlImGuiImageSize(&texture, textureWidth, textureHeight);
	}

	void EditorExtensions::DrawRawTexture(const Texture& texture, const rlRectangle& rectangle)
	{
		const float textureWidth = ImGui::GetWindowWidth() - 20;
		const float ratio = static_cast<float>(rectangle.height) / static_cast<float>(rectangle.width);
		const float textureHeight = textureWidth * ratio;
		rlImGuiImageRect(&texture, textureWidth, textureHeight, rectangle);
	}
} // GEngineCore