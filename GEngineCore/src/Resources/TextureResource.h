//
// Created by guillem on 6/9/25.
//

#ifndef TEXTURERESOURCE_H
#define TEXTURERESOURCE_H

#include "raylib.h"
#include "Resource.h"

namespace GEngineCore
{
	class TextureResource : public Resource
	{
	public:
		explicit TextureResource(
			const std::filesystem::path& fullPath,
			const std::filesystem::path& resourcesPath,
			const Texture2D& rawTexture
			);

		static ResourceType GetTypeStatic() { return ResourceType::TEXTURE; }
		ResourceType GetType() override { return GetTypeStatic(); }
		const char* GetTypeName() override { return "Texture"; }

		const Texture2D& GetRawTexture() const;

	private:
		Texture2D _rawTexture;
	};
}

#endif //TEXTURERESOURCE_H
