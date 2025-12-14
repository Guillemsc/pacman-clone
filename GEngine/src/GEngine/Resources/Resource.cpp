//
// Created by guillem on 6/9/25.
//

#include "GEngine/Resources/Resource.h"

namespace GEngine
{
	Resource::Resource(const std::filesystem::path &fullPath, const std::filesystem::path &resourcesPath)
		: _fullPath(fullPath), _resourcesPath(resourcesPath)
	{
		_fullPathStringView = std::string_view(_fullPath.string().c_str());
		_resourcesPathStringView = std::string_view(_resourcesPath.string().c_str());
	}

	std::filesystem::path Resource::GetFullPath() const
	{
		return _fullPath;
	}

	std::filesystem::path Resource::GetResourcesPath() const
	{
		return _resourcesPath;
	}

	std::string_view Resource::GetFullPathStringView() const
	{
		return _fullPathStringView;
	}

	std::string_view Resource::GetResourcesPathStringView() const
	{
		return _resourcesPathStringView;
	}
}
