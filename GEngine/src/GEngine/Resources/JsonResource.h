//
// Created by guillem on 7/23/25.
//

#ifndef JSONRESOURCE_H
#define JSONRESOURCE_H

#include "json.hpp"
#include "Resource.h"

namespace GEngine
{
	class JsonData;

	class JsonResource final : public Resource
	{
	public:
		explicit JsonResource(
			const std::filesystem::path& fullPath,
			const std::filesystem::path& resourcesPath,
			const nlohmann::json& json
			);

		static ResourceType GetTypeStatic() { return ResourceType::JSON; }
		ResourceType GetType() override { return GetTypeStatic(); }
		const char* GetTypeName() override { return "Json"; }

		JsonData GetJson() const;
		std::string GetJsonString() const;

	private:
		nlohmann::json _json;
	};
}

#endif //JSONRESOURCE_H
