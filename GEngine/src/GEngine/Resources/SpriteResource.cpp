//
// Created by guillem on 12/1/25.
//

#include "SpriteResource.h"

#include "GEngine/Extensions/VectorExtensions.h"

namespace GEngine
{
	SpriteResource::SpriteResource(
		const std::filesystem::path &fullPath,
		const std::filesystem::path &resourcesPath,
		const std::string& textureResourcePath
		)
		: Resource(fullPath, resourcesPath), _textureResourcePath(textureResourcePath)
	{
	}

	std::weak_ptr<TextureResource> SpriteResource::GetTextureResource() const
	{
		return _textureResource;
	}

	int SpriteResource::GetRectanglesCount() const
	{
		return _rectangles.size();
	}

	Rectangle SpriteResource::GetRectangle(const int index) const
	{
		return VectorExtensions::GetOrDefault(_rectangles, index, Rectangle());
	}

	void SpriteResource::Dispose()
	{
		_rectangles.clear();
		_textureResource.reset();
	}
}
