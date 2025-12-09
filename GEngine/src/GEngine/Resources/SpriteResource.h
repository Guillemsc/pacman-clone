//
// Created by guillem on 12/1/25.
//

#ifndef SPRITERESOURCE_H
#define SPRITERESOURCE_H

#include <memory>

#include "raylib.h"
#include "Resource.h"

namespace GEngine
{
	class TextureResource;

	class SpriteResource final : public Resource
	{
		friend class SpriteResourceImporter;

	public:
		explicit SpriteResource(
			const std::filesystem::path& fullPath,
			const std::filesystem::path& resourcesPath,
			const std::string& textureResourcePath
			);

		static ResourceType GetTypeStatic() { return ResourceType::SPRITE; }
		ResourceType GetType() override { return GetTypeStatic(); }
		const char* GetTypeName() override { return "Sprite"; }

		std::weak_ptr<TextureResource> GetTextureResource() const;
		int GetRectanglesCount() const;
		rlRectangle GetRectangle(int index) const;

	protected:
		void Dispose() override;

	private:
		const std::string _textureResourcePath;
		std::vector<rlRectangle> _rectangles;
		std::weak_ptr<TextureResource> _textureResource;
	};
}

#endif //SPRITERESOURCE_H
