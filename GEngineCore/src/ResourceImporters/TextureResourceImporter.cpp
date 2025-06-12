//
// Created by guillem on 6/9/25.
//

#include "TextureResourceImporter.h"

#include "raylib.h"
#include "Resources/TextureResource.h"

namespace GEngineCore
{
	TextureResourceImporter::TextureResourceImporter()
	{
	}

	std::shared_ptr<Resource> TextureResourceImporter::Import(
		const std::filesystem::path& fullPath,
		const std::filesystem::path& resourcesPath
		)
	{
		Texture2D rawTexture = LoadTexture(fullPath.c_str());

		if (rawTexture.height == 0 || rawTexture.width == 0)
		{
			return nullptr;
		}

		std::shared_ptr<TextureResource> texture = std::make_shared<TextureResource>(
			fullPath,
			resourcesPath,
			rawTexture
			);

		return texture;
	}

	std::vector<std::string> TextureResourceImporter::GetSupportedExtensions() const
	{
		return std::vector<std::string> {".png", ".jpg"};
	}
} // GEngineCore