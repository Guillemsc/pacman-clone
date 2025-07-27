//
// Created by guillem on 7/26/25.
//

#ifndef FONTRESOURCE_H
#define FONTRESOURCE_H

#include <filesystem>

#include "raylib.h"
#include "Resource.h"
#include "ResourceType.h"

namespace GEngine
{
	class FontResource final : public Resource
	{
	friend class UiTextRendererComponent;

	public:
		explicit FontResource(
			const std::filesystem::path& fullPath,
			const std::filesystem::path& resourcesPath,
			const Font& font
			);

		static ResourceType GetTypeStatic() { return ResourceType::FONT; }
		ResourceType GetType() override { return GetTypeStatic(); }
		const char* GetTypeName() override { return "Font"; }

		[[nodiscard]] Texture2D GetRawTexture() const;

	protected:
		void Dispose() override;

	private:
		Font _rawFont;
	};
}

#endif //FONTRESOURCE_H
