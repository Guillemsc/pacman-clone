//
// Created by guillem on 6/20/25.
//

#ifndef TILEDMAPIMPORTER_H
#define TILEDMAPIMPORTER_H

#include "ResourceImporter.h"

namespace GEngineCore
{
	class TiledMapResource;

	class TiledMapImporter final : public ResourceImporter
	{
	public:
		explicit TiledMapImporter();

		std::shared_ptr<Resource> Import(const std::filesystem::path& fullPath, const std::filesystem::path& resourcesPath) override;
	};
}

#endif //TILEDMAPIMPORTER_H
