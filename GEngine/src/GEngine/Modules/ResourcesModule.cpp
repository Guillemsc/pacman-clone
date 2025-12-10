//
// Created by guillem on 6/9/25.
//

#include "ResourcesModule.h"

#include "GEngine/Raylib/RaylibWrapper.h"
#include "GEngine/Extensions/StringExtensions.h"
#include "GEngine/Extensions/UnorderedMapExtensions.h"
#include "GEngine/Logging/GEngineLog.h"
#include "GEngine/ResourceImporters/FontResourceImporter.h"
#include "GEngine/ResourceImporters/JsonResourceImporter.h"
#include "GEngine/ResourceImporters/SpriteResourceImporter.h"
#include "GEngine/ResourceImporters/TextureResourceImporter.h"
#include "GEngine/ResourceImporters/TiledMapResourceImporter.h"
#include "GEngine/Resources/TextureResource.h"
#include "spdlog/spdlog.h"

namespace GEngine
{
	ResourcesModule::ResourcesModule()
	{
		_resourcesPath = std::filesystem::current_path() / "resources";
	}

	void ResourcesModule::Init(GEngineCoreModules* modules)
	{
		_modules = modules;

		RegisterResourceImporter<TextureResourceImporter>();
		RegisterResourceImporter<JsonResourceImporter>();
		RegisterResourceImporter<FontResourceImporter>();
		RegisterResourceImporter<SpriteResourceImporter>();
		RegisterResourceImporter<TiledMapResourceImporter>();

		ImportAllResources();
		AfterImportAllResources();
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
		const std::optional<std::weak_ptr<Resource>> optionalResource = UnorderedMapExtensions::GetValue(_resourcesPathByResources, path);

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
		GENGINE_INFO("Starting resource import");

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
			_resourcesPathByResources[resourcesPath.string()] = resource;
			_resourcesByResourceImporters.push_back({resource, importer});
		}

		GENGINE_INFO("Finished resource import");
	}

	void ResourcesModule::AfterImportAllResources()
	{
		GENGINE_INFO("Starting after resource import");

		for (auto it = _resourcesByResourceImporters.begin(); it != _resourcesByResourceImporters.end(); ++it)
		{
			const std::shared_ptr<Resource> resource = it->first.lock();
			if (!resource) continue;

			const std::shared_ptr<IResourceImporter> importer = it->second.lock();
			if (!importer) continue;

			importer->AfterImport(resource.get());
		}

		GENGINE_INFO("Finished after resource import");
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
			GENGINE_ERROR(
				"Could not find resources to import, because resources folder does not exist. Folder should be: {}",
				_resourcesPath.string()
				);
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
			_extensionsByResourceImporters,
			extension
			);

		if (!resourceImporter.has_value())
		{
			return std::weak_ptr<IResourceImporter>();
		}

		return resourceImporter.value();
	}
} // GEngineCore