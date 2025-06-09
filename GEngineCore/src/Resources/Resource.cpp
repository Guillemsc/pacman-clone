//
// Created by guillem on 6/9/25.
//

#include "Resources/Resource.h"

namespace GEngineCore
{
	Resource::Resource(const std::uint32_t id, const std::filesystem::path &fullPath, const std::filesystem::path &resourcesPath)
	{
		_id = id;
		_fullPath = fullPath;
		_resourcesPath = resourcesPath;
	}

	std::filesystem::path Resource::GetFullPath() const
	{
		return _fullPath;
	}

	std::filesystem::path Resource::GetResourcesPath() const
	{
		return _resourcesPath;
	}
}
