//
// Created by guillem on 6/9/25.
//

#include "TextureResource.h"

namespace GEngineCore
{
	TextureResource::TextureResource(
		const std::uint32_t id,
		const std::filesystem::path &fullPath,
		const std::filesystem::path &resourcesPath
		) : Resource(id, fullPath, resourcesPath)
	{
	}
} // GEngineCore