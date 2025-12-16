//
// Created by guillem on 12/16/25.
//

#ifndef GUIZMOUIRENDERERCOMMAND_H
#define GUIZMOUIRENDERERCOMMAND_H

#include "GEngine/Colors/Color01.h"
#include "GEngine/Data/CornersRect.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	enum class GuizmoUiRendererCommandType
	{
		LINE,
		CORNERS_RECT_LINES,
		CIRCLE_LINES,
	};

	struct LineGuizmoUiRendererCommand
	{
		glm::vec2 start;
		glm::vec2 end;
		float thickness;
		Color01 color;
	};

	struct CircleLinesGuizmoUiRendererCommand
	{
		glm::vec2 position;
		float radius;
		Color01 color;
	};

	struct CornersRectLinesGuizmoUiRendererCommand
	{
		CornersRect rect;
		float thickness;
		Color01 color;
	};

	struct GuizmoUiRendererCommand
	{
		GuizmoUiRendererCommandType type;

		union
		{
			LineGuizmoUiRendererCommand line;
			CornersRectLinesGuizmoUiRendererCommand cornersRectLines;
			CircleLinesGuizmoUiRendererCommand circleLines;
		};
	};
}

#endif //GUIZMOUIRENDERERCOMMAND_H
