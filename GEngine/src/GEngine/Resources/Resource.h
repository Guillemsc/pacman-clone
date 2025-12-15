//
// Created by guillem on 6/9/25.
//

#ifndef RESOURCE_H
#define RESOURCE_H

#include <cstdint>
#include <filesystem>

#include "ResourceType.h"
#include "GEngine/Objects/GEngineObject.h"

namespace GEngine
{
	class Resource : public GEngineObject
	{
		friend class ResourcesModule;

	public:
		explicit Resource(
			const std::filesystem::path &fullPath,
			const std::filesystem::path &resourcesPath
			);

		static GEngineObjectType GetObjectTypeStatic() { return GEngineObjectType::RESOURCE; }
		GEngineObjectType GetObjectType() override { return GetObjectTypeStatic(); }

		virtual ResourceType GetType() = 0;
		virtual const char* GetTypeName() = 0;

		std::filesystem::path GetFullPath() const;
		std::filesystem::path GetResourcesPath() const;
		const char* GetFullPathString() const;
		const char* GetResourcesPathString() const;

	protected:
		virtual void Dispose() {};

	private:
		const std::filesystem::path _fullPath;
		const std::filesystem::path _resourcesPath;
		std::string _fullPathString;
		std::string _resourcesPathString;
	};
}

#endif //RESOURCE_H
