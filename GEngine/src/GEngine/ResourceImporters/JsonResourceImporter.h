//
// Created by guillem on 7/23/25.
//

#ifndef JSONRESOURCEIMPORTER_H
#define JSONRESOURCEIMPORTER_H

#include "ResourceImporter.h"

namespace GEngine
{
	class JsonResourceImporter final : public ResourceImporter
	{
	public:
		explicit JsonResourceImporter(GEngineCoreModules* modules);

		std::shared_ptr<Resource> Import(const std::filesystem::path& fullPath, const std::filesystem::path& resourcesPath) override;
	};
}

#endif //JSONRESOURCEIMPORTER_H
