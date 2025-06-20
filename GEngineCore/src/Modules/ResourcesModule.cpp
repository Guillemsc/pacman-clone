//
// Created by guillem on 6/9/25.
//

#include "ResourcesModule.h"

#include "raylib.h"
#include "Extensions/StringExtensions.h"
#include "Extensions/UnorderedMapExtensions.h"
#include "ResourceImporters/TextureResourceImporter.h"
#include "ResourceImporters/TiledMapImporter.h"
#include "Resources/TextureResource.h"
#include "spdlog/spdlog.h"

namespace GEngineCore
{
	ResourcesModule::ResourcesModule()
	{
		_resourcesPath = std::filesystem::current_path() / "resources";

		RegisterResourceImporter<TextureResourceImporter>();
		RegisterResourceImporter<TiledMapImporter>();
	}

	void ResourcesModule::Init()
	{
		ImportAllResources();
	}

	void ResourcesModule::Dispose()
	{
		DisposeAllResources();
	}

	const std::vector<std::shared_ptr<Resource>>& ResourcesModule::GetResources()
	{
		return _resources;
	}

	std::weak_ptr<Resource> ResourcesModule::GetResource(const std::string &path) const
	{
		const std::optional<std::weak_ptr<Resource>> optionalResource = UnorderedMapExtensions::GetValue(_resourcesByResourcePath, path);

		if (!optionalResource.has_value())
		{
			return std::weak_ptr<Resource>();
		}

		return optionalResource.value();
	}


	std::filesystem::path ResourcesModule::FullPathToRelativeResourcesPath(const std::filesystem::path &path) const
	{
		return std::filesystem::relative(path, _resourcesPath);
	}

	std::filesystem::path ResourcesModule::RelativeResourcesPathToFullPath(const std::filesystem::path &path) const
	{
		return _resourcesPath / path;
	}

	void ResourcesModule::ImportAllResources()
	{
		std::vector<std::filesystem::path> paths = GetAllResourcesPathsToImport();

		for (auto it = paths.begin(); it != paths.end(); ++it)
		{
			std::filesystem::path extension = it->extension();
			std::string extensionString = StringExtensions::ToLower(extension.string());

			const std::shared_ptr<IResourceImporter> importer = GetImporterForExtension(extensionString).lock();
			if (!importer) continue;

			std::filesystem::path resourcesPath = FullPathToRelativeResourcesPath(*it);

			const std::shared_ptr<Resource> resource = importer->Import(*it, resourcesPath);
			if (!resource) continue;

			_resources.push_back(resource);
			_resourcesByResourcePath[resourcesPath] = resource;
		}
	}

	void ResourcesModule::DisposeAllResources()
	{
		for (auto it = _resources.begin(); it != _resources.end(); ++it)
		{
			(*it)->Dispose();
		}

		_resources.clear();
	}

	std::vector<std::filesystem::path> ResourcesModule::GetAllResourcesPathsToImport() const
	{
		std::vector<std::filesystem::path> files;

		if (!std::filesystem::exists(_resourcesPath) || !std::filesystem::is_directory(_resourcesPath))
		{
			spdlog::error("Could not get resources to import, because resources folder does not exist");
			return files;
		}

		for (const auto& entry : std::filesystem::recursive_directory_iterator(_resourcesPath))
		{
			if (entry.is_regular_file())
			{
				files.push_back(entry.path());
			}
		}

		return files;
	}

	std::weak_ptr<IResourceImporter> ResourcesModule::GetImporterForExtension(const std::string &extension) const
	{
		const std::optional<std::weak_ptr<IResourceImporter>> resourceImporter = UnorderedMapExtensions::GetValue(
			_extensionByResourceImporter,
			extension
			);

		if (!resourceImporter.has_value())
		{
			return std::weak_ptr<IResourceImporter>();
		}

		return resourceImporter.value();
	}
} // GEngineCore