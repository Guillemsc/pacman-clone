//
// Created by guillem on 7/23/25.
//

#ifndef JSONRESOURCE_H
#define JSONRESOURCE_H

#include "json.hpp"
#include "Resource.h"
#include "GEngine/Data/JsonData.h"

namespace GEngine
{
	class JsonResource final : public Resource
	{
	public:
		explicit JsonResource(
			const std::filesystem::path& fullPath,
			const std::filesystem::path& resourcesPath,
			const JsonData& json
			);

		static ResourceType GetTypeStatic() { return ResourceType::JSON; }
		ResourceType GetType() override { return GetTypeStatic(); }
		const char* GetTypeName() override { return "Json"; }

		[[nodiscard]] JsonData GetJson() const;
		[[nodiscard]] std::string GetJsonString() const;

	private:
		JsonData _json;
	};
}

#endif //JSONRESOURCE_H
