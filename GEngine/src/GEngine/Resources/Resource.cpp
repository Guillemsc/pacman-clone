//
// Created by guillem on 6/9/25.
//

#include "GEngine/Resources/Resource.h"

namespace GEngine
{
	Resource::Resource(const std::filesystem::path &fullPath, const std::filesystem::path &resourcesPath)
		: _fullPath(fullPath), _resourcesPath(resourcesPath)
	{
		_fullPathString = _fullPath.string();
		_resourcesPathString = _resourcesPath.string();
	}

	std::filesystem::path Resource::GetFullPath() const
	{
		return _fullPath;
	}

	std::filesystem::path Resource::GetResourcesPath() const
	{
		return _resourcesPath;
	}

	const char* Resource::GetFullPathString() const
	{
		return _fullPathString.c_str();
	}

	const char* Resource::GetResourcesPathString() const
	{
		return _resourcesPathString.c_str();
	}
}
