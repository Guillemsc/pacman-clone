//
// Created by guillem on 12/16/25.
//

#ifndef GUIZMORENDERER2DCOMMAND_H
#define GUIZMORENDERER2DCOMMAND_H

#include "GEngine/Colors/Color01.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	enum class GuizmoRenderer2dCommandType
	{
		LINE,
		RECT,
		RECT_LINES,
		CIRCLE_LINES,
	};

	struct LineGuizmoRenderer2dCommand
	{
		glm::vec2 start;
		glm::vec2 end;
		float thickness;
		Color01 color;
	};

	struct RectGuizmoRenderer2dCommand
	{
		glm::vec2 position;
		float rotationRadians;
		glm::vec2 size;
		Color01 color;
	};

	struct RectLinesGuizmoRenderer2dCommand
	{
		glm::vec2 position;
		float rotationRadians;
		glm::vec2 size;
		float thickness;
		Color01 color;
	};

	struct CircleLinesGuizmoRenderer2dCommand
	{
		glm::vec2 position;
		float radius;
		Color01 color;
	};

	struct GuizmoRenderer2dCommand
	{
		GuizmoRenderer2dCommandType type;

		union
		{
			LineGuizmoRenderer2dCommand line;
			RectGuizmoRenderer2dCommand rect;
			RectLinesGuizmoRenderer2dCommand rectLines;
			CircleLinesGuizmoRenderer2dCommand circleLines;
		};
	};
}

#endif //GUIZMORENDERER2DCOMMAND_H
