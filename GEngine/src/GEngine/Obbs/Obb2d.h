//
// Created by guillem on 12/2/25.
//

#ifndef OBB2D_H
#define OBB2D_H

#include "glm/vec2.hpp"

namespace GEngine
{
	class Obb2d
	{
	public:
		Obb2d();
		Obb2d(const glm::vec2& center, const glm::vec2& size, float rotationRadians);

		bool Intersects(const Obb2d& other) const;
		void GetCorners(glm::vec2 out[4]) const;

	private:
		float ProjectExtent(const glm::vec2& axis) const;

	private:
		glm::vec2 _center = glm::vec2(0);
		glm::vec2 _halfExtents = glm::vec2(0);
		glm::vec2 _axisX = glm::vec2(0);
		glm::vec2 _axisY = glm::vec2(0);
		float _radius = 0.0f;
	};
}

#endif //OBB2D_H
