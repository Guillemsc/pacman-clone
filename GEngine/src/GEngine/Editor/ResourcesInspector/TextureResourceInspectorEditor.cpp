//
// Created by guillem on 6/18/25.
//

#include "TextureResourceInspectorEditor.h"

#include "imgui.h"
#include "rlImGui.h"
#include "GEngine/Editor/Extensions/EditorExtensions.h"

namespace GEngine
{
	TextureResourceInspectorEditor::TextureResourceInspectorEditor(GEngineCoreModules* modules)
		: ResourceInspectorEditor(modules)
	{
	}

	void TextureResourceInspectorEditor::DrawSpecific(const std::shared_ptr<TextureResource> &inspect)
	{
		const Texture& rawTexture = inspect->GetRawTexture();

		ImGui::Text("Size [width: %d] [height: %d]", rawTexture.width, rawTexture.height);

		const bool canDraw = rawTexture.height > 0 && rawTexture.width > 0;

		if (canDraw)
		{
			EditorExtensions::DrawRawTexture(rawTexture);
		}
	}
} // GEngineCore