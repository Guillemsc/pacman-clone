//
// Created by guillem on 12/16/25.
//

#ifndef UIRENDERERCOMMAND_H
#define UIRENDERERCOMMAND_H

#include "GEngine/Colors/Color01.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	enum class UiRendererCommandType
	{
		RECT,
	};

	struct RectUiRendererCommand
	{
		glm::vec2 position;
		float rotationRadians;
		glm::vec2 size;
		glm::vec2 center;
		Color01 color;
	};

	struct UiRendererCommand
	{
		UiRendererCommandType type;

		union
		{
			RectUiRendererCommand rect;
		};
	};
}

#endif //UIRENDERERCOMMAND_H
