//
// Created by guillem on 7/26/25.
//

#ifndef FONTRESOURCEIMPORTER_H
#define FONTRESOURCEIMPORTER_H

#include "ResourceImporter.h"

namespace GEngine
{
	class FontResourceImporter  final : public ResourceImporter
	{
	public:
		explicit FontResourceImporter(GEngineCoreModules* modules);

		std::shared_ptr<Resource> Import(const std::filesystem::path& fullPath, const std::filesystem::path& resourcesPath) override;
	};
}

#endif //FONTRESOURCEIMPORTER_H
