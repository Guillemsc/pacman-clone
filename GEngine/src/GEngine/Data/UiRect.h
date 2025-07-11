//
// Created by guillem on 7/8/25.
//

#ifndef UIRECT_H
#define UIRECT_H

#include <vector>

#include "CornersRect.h"
#include "glm/fwd.hpp"
#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

namespace GEngine
{
	struct UiRect
	{
		static UiRect Transform(const UiRect& parent, const UiRect& child);
		glm::mat4 BuildMatrix() const;
		glm::vec2 GetPivotOffset(const glm::vec2& pivot) const;
		glm::vec2 GetPivotOffset() const;
		glm::vec2 GetPivotPosition(const glm::vec2& pivot) const;
		glm::vec2 GetPivotPosition() const;
		glm::vec2 GetPointFromNormalizedPoint(const glm::vec2& point) const;
		glm::vec4 GetRectFromNormalizedRect(const glm::vec4& point) const;
		CornersRect GetCorners() const;
		bool ContainsPoint(const glm::vec2& point) const;

		glm::vec2 position = glm::vec2(0);
		float rotation = 0;
		glm::vec2 scale = glm::vec2(1);

		glm::vec2 size = glm::vec2(0);
		glm::vec2 pivot = glm::vec2(0.5f);
	};
}

#endif //UIRECT_H
