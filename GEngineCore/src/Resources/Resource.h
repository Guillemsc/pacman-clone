//
// Created by guillem on 6/9/25.
//

#ifndef RESOURCE_H
#define RESOURCE_H

#include <cstdint>
#include <filesystem>

#include "ResourceType.h"
#include "Objects/GEngineObject.h"

namespace GEngineCore
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

	protected:
		virtual void Dispose() {};

	private:
		std::filesystem::path _fullPath;
		std::filesystem::path _resourcesPath;
	};
}

#endif //RESOURCE_H
