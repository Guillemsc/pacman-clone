//
// Created by guillem on 6/9/25.
//

#ifndef RESOURCEIMPORTER_H
#define RESOURCEIMPORTER_H

#include <filesystem>
#include <memory>
#include <vector>

namespace GEngineCore
{
	class Resource;

	class IResourceImporter
	{
	public:
		virtual ~IResourceImporter() = default;

		virtual std::shared_ptr<Resource> Import(const std::filesystem::path& fullPath, const std::filesystem::path& resourcesPath) = 0;
		[[nodiscard]] virtual std::vector<std::string> GetSupportedExtensions() const = 0;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class T>
	class ResourceImporter : public IResourceImporter
	{

	};
}

#endif //RESOURCEIMPORTER_H
