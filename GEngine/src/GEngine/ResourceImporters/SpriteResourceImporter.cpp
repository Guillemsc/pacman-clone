//
// Created by guillem on 12/1/25.
//

#include "SpriteResourceImporter.h"

#include <fstream>

#include "json.hpp"
#include "GEngine/Data/JsonData.h"
#include "GEngine/Modules/ResourcesModule.h"
#include "GEngine/Resources/SpriteResource.h"
#include "GEngine/Resources/TextureResource.h"
#include "spdlog/spdlog.h"

namespace GEngine
{
	SpriteResourceImporter::SpriteResourceImporter(GEngineCoreModules *modules)
		: ResourceImporter(modules)
	{
		AddSupportedExtension(".sprite");
	}

	std::shared_ptr<Resource> SpriteResourceImporter::Import(
		const std::filesystem::path &fullPath,
		const std::filesystem::path &resourcesPath
		)
	{
		const std::ifstream file(fullPath);
		if (!file) return nullptr;

		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string contents = buffer.str();

		nlohmann::json json;

		try
		{
			json = nlohmann::json::parse(contents);
		}
		catch (const nlohmann::json::parse_error& error)
		{
			//std::cerr << "JSON parse error: " << e.what() << std::endl;
			//std::cerr << "Exception ID: " << e.id << "\n";
			//std::cerr << "Byte position: " << e.byte << "\n";
			spdlog::error("Sprite parse error");
			return nullptr;
		}

		JsonData jsonData = JsonData(json);
		std::string textureResourcePath = jsonData.GetString("texture");

		std::shared_ptr<SpriteResource> resource = std::make_shared<SpriteResource>(
			fullPath,
			resourcesPath,
			textureResourcePath
			);

		std::int32_t rects = jsonData.GetArrayCount("rects");

		for (std::size_t i = 0; i < rects; i++)
		{
			JsonData rectData = jsonData.GetArrayObject("rects", i);
			std::size_t x = rectData.GetInt("x");
			std::size_t y = rectData.GetInt("y");
			std::size_t w = rectData.GetInt("w");
			std::size_t h = rectData.GetInt("h");

			Rectangle rect(x, y, w, h);

			resource->_rectangles.push_back(rect);
		}

		return resource;
	}

	void SpriteResourceImporter::AfterImport(Resource *resource)
	{
		SpriteResource* spriteResource = static_cast<SpriteResource*>(resource);
		spriteResource->_textureResource = _modules->resources->GetResource<TextureResource>(spriteResource->_textureResourcePath);
	}
}
