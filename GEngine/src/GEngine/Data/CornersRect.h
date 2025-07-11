//
// Created by guillem on 7/11/25.
//

#ifndef CORNERSRECT_H
#define CORNERSRECT_H

#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

namespace GEngine
{
	struct CornersRect
	{
		CornersRect GetFromNormalisedRect(const glm::vec4& rect) const;
		glm::vec2 GetCenter() const;
		glm::vec2 GetSize() const;

		glm::vec2 bottomLeft = glm::vec2(0.0f);
		glm::vec2 topLeft = glm::vec2(0.0f);
		glm::vec2 topRight = glm::vec2(0.0f);
		glm::vec2 bottomRight = glm::vec2(0.0f);
	};
}

#endif //CORNERSRECT_H
