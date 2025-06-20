//
// Created by guillem on 6/18/25.
//

#include "TextureResourceInspectorEditor.h"

#include "imgui.h"
#include "rlImGui.h"

namespace GEngineCore
{
	void TextureResourceInspectorEditor::DrawSpecific(const std::shared_ptr<TextureResource> &inspect)
	{
		const Texture& rawTexture = inspect->GetRawTexture();

		ImGui::Text("Size [width: %d] [height: %d]", rawTexture.width, rawTexture.height);

		const bool canDraw = rawTexture.height > 0 && rawTexture.width > 0;

		if (canDraw)
		{
			const float textureWidth = ImGui::GetWindowWidth() - 20;
			const float ratio = static_cast<float>(rawTexture.height) / static_cast<float>(rawTexture.width);
			const float textureHeight = textureWidth * ratio;
			rlImGuiImageSize(&rawTexture, textureWidth, textureHeight);
		}
	}
} // GEngineCore