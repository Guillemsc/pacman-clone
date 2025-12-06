//
// Created by guillem on 7/23/25.
//

#include "JsonResource.h"

#include "GEngine/Data/JsonData.h"

namespace GEngine
{
	JsonResource::JsonResource(
		const std::filesystem::path &fullPath,
		const std::filesystem::path &resourcesPath,
		const JsonData &json
		)
	: Resource(fullPath, resourcesPath)
	{
		_json = json;
	}

	JsonData JsonResource::GetJson() const
	{
		return _json;
	}

	std::string JsonResource::GetJsonString() const
	{
		return _json.Dump(4);
	}
}
