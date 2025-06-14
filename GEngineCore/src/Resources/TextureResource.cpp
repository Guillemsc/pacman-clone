//
// Created by guillem on 6/9/25.
//

#include "TextureResource.h"

namespace GEngineCore
{
	TextureResource::TextureResource(
		const std::filesystem::path &fullPath,
		const std::filesystem::path &resourcesPath,
		const Texture2D& rawTexture
		) : Resource(fullPath, resourcesPath)
	{
		_rawTexture = rawTexture;
	}

	const Texture2D& TextureResource::GetRawTexture() const
	{
		return _rawTexture;
	}

	void TextureResource::Dispose()
	{
		UnloadTexture(_rawTexture);
		_rawTexture = Texture2D();
	}
} // GEngineCore