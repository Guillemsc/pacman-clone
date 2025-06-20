//
// Created by guillem on 6/9/25.
//

#ifndef TEXTURERESOURCEIMPORTER_H
#define TEXTURERESOURCEIMPORTER_H

#include "ResourceImporter.h"

namespace GEngineCore
{
	class TextureResource;

	class TextureResourceImporter final : public ResourceImporter
	{
	public:
		explicit TextureResourceImporter();

		std::shared_ptr<Resource> Import(const std::filesystem::path& fullPath, const std::filesystem::path& resourcesPath) override;
	};
}

#endif //TEXTURERESOURCEIMPORTER_H
