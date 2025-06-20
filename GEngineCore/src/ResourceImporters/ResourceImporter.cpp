//
// Created by guillem on 6/9/25.
//

#include "ResourceImporter.h"

namespace GEngineCore
{
	const std::vector<std::string>& ResourceImporter::GetSupportedExtensions() const
	{
		return _supportedExtensions;
	}

	void ResourceImporter::AddSupportedExtension(const std::string &extension)
	{
		_supportedExtensions.push_back(extension);
	}
}
