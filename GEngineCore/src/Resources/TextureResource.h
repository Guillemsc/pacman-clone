//
// Created by guillem on 6/9/25.
//

#ifndef TEXTURERESOURCE_H
#define TEXTURERESOURCE_H

#include "Resource.h"

namespace GEngineCore
{
	class TextureResource : public Resource
	{
	public:
		explicit TextureResource(
			std::uint32_t id,
			const std::filesystem::path& fullPath,
			const std::filesystem::path& resourcesPath
			);

		static ResourceType GetTypeStatic() { return ResourceType::TEXTURE; }
		ResourceType GetType() override { return GetTypeStatic(); }
		const char* GetTypeName() override { return "Texture"; }
	};
}

#endif //TEXTURERESOURCE_H
