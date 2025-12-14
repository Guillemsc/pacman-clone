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
		std::string_view GetFullPathStringView() const;
		std::string_view GetResourcesPathStringView() const;

	protected:
		virtual void Dispose() {};

	private:
		const std::filesystem::path _fullPath;
		const std::filesystem::path _resourcesPath;
		std::string_view _fullPathStringView;
		std::string_view _resourcesPathStringView;
	};
}

#endif //RESOURCE_H
