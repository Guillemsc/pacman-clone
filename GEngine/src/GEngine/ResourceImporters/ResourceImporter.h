//
// Created by guillem on 6/9/25.
//

#ifndef RESOURCEIMPORTER_H
#define RESOURCEIMPORTER_H

#include <filesystem>
#include <memory>
#include <vector>

#include "GEngine/Core/GEngineCoreModules.h"

namespace GEngine
{
	class GEngineCoreApplication;
	class Resource;

	class IResourceImporter
	{
	public:
		virtual ~IResourceImporter() = default;

		virtual std::shared_ptr<Resource> Import(const std::filesystem::path& fullPath, const std::filesystem::path& resourcesPath) = 0;
		virtual void AfterImport(const Resource* resource) {};
		[[nodiscard]] virtual const std::vector<std::string>& GetSupportedExtensions() const = 0;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	class ResourceImporter : public IResourceImporter
	{
	public:
		explicit ResourceImporter(GEngineCoreModules* modules);

		[[nodiscard]] const std::vector<std::string>& GetSupportedExtensions() const override;

	protected:
		void AddSupportedExtension(const std::string& extension);

	protected:
		GEngineCoreModules* const _modules;

	private:
		std::vector<std::string> _supportedExtensions;
	};
}

#endif //RESOURCEIMPORTER_H
