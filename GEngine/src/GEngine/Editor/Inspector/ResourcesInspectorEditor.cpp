//
// Created by guillem on 6/18/25.
//

#include "ResourcesInspectorEditor.h"

#include <format>

#include "imgui.h"
#include "GEngine/Editor/ResourcesInspector/FontResourceInspectorEditor.h"
#include "GEngine/Editor/ResourcesInspector/JsonResourceInspectorEditor.h"
#include "GEngine/Editor/ResourcesInspector/SpriteResourceInspectorEditor.h"
#include "GEngine/Editor/ResourcesInspector/TextureResourceInspectorEditor.h"
#include "GEngine/Editor/ResourcesInspector/TiledMapResourceInspectorEditor.h"
#include "GEngine/Resources/Resource.h"

namespace GEngine
{
	ResourcesInspectorEditor::ResourcesInspectorEditor(GEngineCoreModules* modules)
		: GEngineObjectInspectorEditor(modules)
	{
		RegisterInspector<TextureResourceInspectorEditor, TextureResource>();
		RegisterInspector<JsonResourceInspectorEditor, JsonResource>();
		RegisterInspector<FontResourceInspectorEditor, FontResource>();
		RegisterInspector<SpriteResourceInspectorEditor, SpriteResource>();
		RegisterInspector<TiledMapResourceInspectorEditor, TiledMapResource>();
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

			const char* path = inspect->GetResourcesPathString();
			ImGui::Text("%s", std::format("Path: {0}", path).c_str());

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