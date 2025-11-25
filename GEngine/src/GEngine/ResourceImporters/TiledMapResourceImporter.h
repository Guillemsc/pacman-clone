//
// Created by guillem on 6/20/25.
//

#ifndef TILEDMAPIMPORTER_H
#define TILEDMAPIMPORTER_H

#include "ResourceImporter.h"

namespace GEngine
{
	class TiledMapResource;

	class TiledMapResourceImporter final : public ResourceImporter
	{
	public:
		explicit TiledMapResourceImporter(GEngineCoreModules* modules);

		std::shared_ptr<Resource> Import(const std::filesystem::path& fullPath, const std::filesystem::path& resourcesPath) override;
		void AfterImport(const Resource* resource) override;
	};
}

#endif //TILEDMAPIMPORTER_H
