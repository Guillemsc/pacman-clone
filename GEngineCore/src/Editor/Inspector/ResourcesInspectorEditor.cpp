//
// Created by guillem on 6/18/25.
//

#include "ResourcesInspectorEditor.h"

#include "imgui.h"
#include "Editor/ResourcesInspector/TextureResourceInspectorEditor.h"
#include "Resources/Resource.h"

namespace GEngineCore
{
	ResourcesInspectorEditor::ResourcesInspectorEditor()
	{
		RegisterInspector<TextureResourceInspectorEditor, TextureResource>();
	}

	void ResourcesInspectorEditor::DrawSpecific(const std::shared_ptr<Resource> &inspect)
	{
		const std::shared_ptr<IResourceInspectorEditor> inspector = GetInspectorEditor(inspect->GetType());

		const char* name = inspect->GetTypeName();

		if (ImGui::CollapsingHeader(name, ImGuiTreeNodeFlags_Leaf))
		{
			if (!inspector)
			{
				ImGui::Text("Cannot be inspected");
				return;;
			}

			inspector->Draw(inspect);
		}
	}

	std::shared_ptr<IResourceInspectorEditor> ResourcesInspectorEditor::GetInspectorEditor(const ResourceType resourceType)
	{
		const std::size_t objectIndex = static_cast<std::size_t>(resourceType);

		if (_inspectorEditors.size() <= objectIndex)
		{
			return nullptr;
		}

		return _inspectorEditors[objectIndex];
	}
} // GEngineCore