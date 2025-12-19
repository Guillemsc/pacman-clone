//
// Created by guillem on 12/16/25.
//

#ifndef UIRENDERERCOMMAND_H
#define UIRENDERERCOMMAND_H

#include "GEngine/Colors/Color01.h"
#include "GEngine/Resources/FontResource.h"
#include "GEngine/Text/HorizontalTextAlign.h"
#include "GEngine/Text/VerticalTextAlign.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	enum class UiRendererCommandType
	{
		TEXTURE,
		RECT,
		TEXT,
	};

	struct TextureUiRendererCommand
	{
		Texture2D texture;
		glm::vec2 position;
		float rotationRadians;
		glm::vec2 size;
		glm::vec2 pivot;
		Color01 color;
	};

	struct RectUiRendererCommand
	{
		glm::vec2 position;
		float rotationRadians;
		glm::vec2 size;
		glm::vec2 pivot;
		Color01 color;
	};

	struct TextUiRendererCommand
	{
		FontResource* font;
		std::string_view text;
		glm::vec2 position;
		float rotationRadians;
		glm::vec2 size;
		glm::vec2 pivot;
		float wordSpacing;
		Color01 color;
		HorizontalTextAlign horizontalAlign;
		VerticalTextAlign verticalAlign;
	};

	struct UiRendererCommand
	{
		UiRendererCommandType type;

		union
		{
			TextureUiRendererCommand texture;
			RectUiRendererCommand rect;
			TextUiRendererCommand text;
		};
	};
}

#endif //UIRENDERERCOMMAND_H
