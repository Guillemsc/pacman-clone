//
// Created by guillem on 12/1/25.
//

#ifndef SPRITERESOURCEIMPORTER_H
#define SPRITERESOURCEIMPORTER_H

#include "ResourceImporter.h"

namespace GEngine
{
	class SpriteResourceImporter final : public ResourceImporter
	{
	public:
		explicit SpriteResourceImporter(GEngineCoreModules* modules);

		std::shared_ptr<Resource> Import(const std::filesystem::path& fullPath, const std::filesystem::path& resourcesPath) override;
		void AfterImport(Resource* resource) override;
	};
}

#endif //SPRITERESOURCEIMPORTER_H
