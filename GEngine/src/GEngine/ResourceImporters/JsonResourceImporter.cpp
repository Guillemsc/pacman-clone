//
// Created by guillem on 7/23/25.
//

#include "JsonResourceImporter.h"

#include <fstream>

#include "GEngine/Resources/JsonResource.h"
#include "spdlog/spdlog.h"

namespace GEngine
{
	JsonResourceImporter::JsonResourceImporter(GEngineCoreModules* modules)
		: ResourceImporter(modules)
	{
		AddSupportedExtension(".json");
	}

	std::shared_ptr<Resource> JsonResourceImporter::Import(
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
			spdlog::error("JSON parse error");
			return nullptr;
		}

		std::shared_ptr<JsonResource> resource = std::make_shared<JsonResource>(
			fullPath,
			resourcesPath,
			json
			);

		return resource;
	}
} // GEngine