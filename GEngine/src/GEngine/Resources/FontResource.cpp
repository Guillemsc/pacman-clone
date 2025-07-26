//
// Created by guillem on 7/26/25.
//

#include "FontResource.h"

namespace GEngine
{
	FontResource::FontResource(
		const std::filesystem::path &fullPath,
		const std::filesystem::path &resourcesPath,
		const Font &font
		)
	: Resource(fullPath, resourcesPath)
	{
		_font = font;
	}

	Texture2D FontResource::GetRawTexture() const
	{
		return _font.texture;
	}
}
