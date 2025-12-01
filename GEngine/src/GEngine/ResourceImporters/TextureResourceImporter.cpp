//
// Created by guillem on 6/9/25.
//

#include "TextureResourceImporter.h"

#include "GEngine/Raylib/RaylibWrapper.h"
#include "GEngine/Resources/TextureResource.h"

namespace GEngine
{
	TextureResourceImporter::TextureResourceImporter(GEngineCoreModules* modules)
		: ResourceImporter(modules)
	{
		AddSupportedExtension(".png");
		AddSupportedExtension(".jpg");
	}

	std::shared_ptr<Resource> TextureResourceImporter::Import(
		const std::filesystem::path& fullPath,
		const std::filesystem::path& resourcesPath
		)
	{
		const char* pathChar = fullPath.c_str();
		Texture2D rawTexture = LoadTexture(pathChar);

		if (rawTexture.id == 0)
		{
			return nullptr;
		}

		std::shared_ptr<TextureResource> resource = std::make_shared<TextureResource>(
			fullPath,
			resourcesPath,
			rawTexture
			);

		return resource;
	}
} // GEngineCore