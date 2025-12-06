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
		JsonData data = JsonData::LoadFromFile(fullPath.c_str());

		if (!data.HasData()) return nullptr;

		std::shared_ptr<JsonResource> resource = std::make_shared<JsonResource>(
			fullPath,
			resourcesPath,
			data
			);

		return resource;
	}
} // GEngine