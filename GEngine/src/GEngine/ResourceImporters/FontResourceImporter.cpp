//
// Created by guillem on 7/26/25.
//

#include "FontResourceImporter.h"

#include "raylib.h"
#include "GEngine/Resources/FontResource.h"

namespace GEngine
{
	FontResourceImporter::FontResourceImporter(const std::weak_ptr<GEngineCoreApplication> &app) : ResourceImporter(app)
	{
		AddSupportedExtension(".ttf");
	}

	std::shared_ptr<Resource> FontResourceImporter::Import(
		const std::filesystem::path &fullPath,
		const std::filesystem::path &resourcesPath
		)
	{
		Font rawFont = LoadFont(fullPath.c_str());

		if (rawFont.glyphCount == 0 || rawFont.texture.id == 0)
		{
			return nullptr;
		}

		std::shared_ptr<FontResource> resource = std::make_shared<FontResource>(
			fullPath,
			resourcesPath,
			rawFont
			);

		return resource;
	}
}
