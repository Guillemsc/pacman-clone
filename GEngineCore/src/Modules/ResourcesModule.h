//
// Created by guillem on 6/9/25.
//

#ifndef RESOURCESMODULE_H
#define RESOURCESMODULE_H

#include <memory>
#include <unordered_map>
#include <vector>

#include "ResourceImporters/ResourceImporter.h"
#include "Resources/ResourceType.h"

namespace GEngineCore
{
	class Resource;

	class ResourcesModule
	{
	public:
		ResourcesModule();

		void Init();
		void Dispose();

		const std::vector<std::shared_ptr<Resource>>& GetResources();
		std::weak_ptr<Resource> GetResource(const std::string& path) const;
		template <class T>
		std::weak_ptr<T> GetResource(const std::string& path) const;

		std::filesystem::path FullPathToRelativeResourcesPath(const std::filesystem::path& path) const;
		std::filesystem::path RelativeResourcesPathToFullPath(const std::filesystem::path& path) const;

	private:
		void ImportAllResources();
		void DisposeAllResources();

		std::vector<std::filesystem::path> GetAllResourcesPathsToImport() const;

		std::weak_ptr<IResourceImporter> GetImporterForExtension(const std::string& extension) const;

		template <class TImporter>
		void RegisterResourceImporter();

	private:
		std::filesystem::path _resourcesPath;

		std::vector<std::shared_ptr<IResourceImporter>> _resourceImporters;
		std::unordered_map<std::string, std::weak_ptr<IResourceImporter>> _extensionByResourceImporter;

		std::vector<std::shared_ptr<Resource>> _resources;
		std::unordered_map<std::string, std::weak_ptr<Resource>> _resourcesByResourcePath;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class T>
	std::weak_ptr<T> ResourcesModule::GetResource(const std::string &path) const
	{
		static_assert(std::is_base_of_v<Resource, T>, "T is not derived from Resource");

		const std::weak_ptr<Resource> resourcePtr = GetResource(path);

		const std::shared_ptr<Resource> resource = resourcePtr.lock();
		if (!resource) return std::weak_ptr<T>();

		return std::static_pointer_cast<T>(resource);
	}

	template<class TImporter>
	void ResourcesModule::RegisterResourceImporter()
	{
		static_assert(std::is_base_of_v<ResourceImporter, TImporter>, "TImporter is not derived from ResourceImporter");

		std::shared_ptr<TImporter> importer = std::make_shared<TImporter>();
		_resourceImporters.push_back(importer);

		std::vector<std::string> supportedExtensions = importer->GetSupportedExtensions();

		for (auto it = supportedExtensions.begin(); it != supportedExtensions.end(); ++it)
		{
			_extensionByResourceImporter[*it] = importer;
		}
	}
}

#endif //RESOURCESMODULE_H
