//
// Created by guillem on 6/9/25.
//

#include "GEngine/Resources/Resource.h"

namespace GEngine
{
	Resource::Resource(const std::filesystem::path &fullPath, const std::filesystem::path &resourcesPath)
		: _fullPath(fullPath), _resourcesPath(resourcesPath)
	{
		
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
