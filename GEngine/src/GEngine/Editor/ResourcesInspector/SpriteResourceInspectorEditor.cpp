//
// Created by guillem on 12/1/25.
//

#include "SpriteResourceInspectorEditor.h"

#include "imgui.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Editor/Extensions/EditorExtensions.h"
#include "GEngine/Resources/TextureResource.h"

namespace GEngine
{
	SpriteResourceInspectorEditor::SpriteResourceInspectorEditor(GEngineCoreModules *modules)
		: ResourceInspectorEditor(modules)
	{
	}

	void SpriteResourceInspectorEditor::DrawSpecific(const std::shared_ptr<SpriteResource> &inspect)
	{
		const std::shared_ptr<TextureResource> textureResource = inspect->GetTextureResource().lock();

		EditorExtensions::DrawResource(_modules->editor, "Texture", textureResource);

		const int rectsCount = inspect->GetRectanglesCount();

		for (int i = 0; i < rectsCount; i++)
		{
			const Rectangle rectangle = inspect->GetRectangle(i);
			ImGui::Text("Rect %d [x: %.1f] [y: %.1f] [w: %.1f] [h: %.1f]", i, rectangle.x, rectangle.y, rectangle.width, rectangle.height);

			if (textureResource)
			{
				const Texture& rawTexture = textureResource->GetRawTexture();
				EditorExtensions::DrawRawTexture(rawTexture, rectangle);
			}
		}
	}
}
