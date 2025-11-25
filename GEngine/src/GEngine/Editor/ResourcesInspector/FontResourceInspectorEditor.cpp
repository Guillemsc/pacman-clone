//
// Created by guillem on 7/26/25.
//

#include "FontResourceInspectorEditor.h"

#include "GEngine/Editor/Extensions/EditorExtensions.h"

namespace GEngine
{
	FontResourceInspectorEditor::FontResourceInspectorEditor(GEngineCoreModules* modules)
		: ResourceInspectorEditor(modules)
	{
	}

	void FontResourceInspectorEditor::DrawSpecific(const std::shared_ptr<FontResource> &inspect)
	{
		const Texture& rawTexture = inspect->GetRawTexture();

		EditorExtensions::DrawRawTexture(rawTexture);
	}
}
