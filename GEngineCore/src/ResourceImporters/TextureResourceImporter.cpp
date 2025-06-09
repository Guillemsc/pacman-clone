//
// Created by guillem on 6/9/25.
//

#include "TextureResourceImporter.h"

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
		std::shared_ptr<TextureResource> texture = std::make_shared<TextureResource>(
			32,
			fullPath,
			resourcesPath
			);

		return texture;
	}

	std::vector<std::string> TextureResourceImporter::GetSupportedExtensions() const
	{
		return std::vector<std::string> {".png", ".jpg"};
	}
} // GEngineCore