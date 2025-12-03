//
// Created by guillem on 12/2/25.
//

#include "Obb2d.h"

#include "glm/detail/func_geometric.inl"

namespace GEngine
{
	Obb2d::Obb2d()
	{
	}

	Obb2d::Obb2d(const glm::vec2 &center, const glm::vec2 &size, const float rotationRadians)
	: _center(center), _halfExtents(size * 0.5f)
	{
		const float cos = std::cos(rotationRadians);
		const float sin = std::sin(rotationRadians);

		_axisX = glm::vec2(cos, sin);
		_axisY = glm::vec2(-sin, cos);

		_radius = glm::length(_halfExtents);
	}

	bool Obb2d::Intersects(const Obb2d &other) const
	{
		// Fast sphere test
		const float radiiCombined = _radius + other._radius;
		const glm::vec2 centersDistance = other._center - _center;
		if (glm::dot(centersDistance, centersDistance) > radiiCombined * radiiCombined)
		{
			return false;
		}

		// SAT test
		const glm::vec2 centerDistance = other._center - _center;

		const glm::vec2 axes[4] = { _axisX, _axisY, other._axisX, other._axisY };

		for (int i = 0; i < 4; ++i)
		{
			const glm::vec2& axis = axes[i];

			const float dist = std::abs(glm::dot(centerDistance, axis));
			const float projA = ProjectExtent(axis);
			const float projB = other.ProjectExtent(axis);

			if (dist > projA + projB)
			{
				return false; // Separation axis found, no intersection
			}
		}

		return true; // No separating axis, they intersect
	}

	void Obb2d::GetCorners(glm::vec2 out[4]) const
	{
		const glm::vec2 halfExtentsOnAxisX = _axisX * _halfExtents.x;
		const glm::vec2 halfExtentsOnAxisY = _axisY * _halfExtents.y;

		out[0] = _center + halfExtentsOnAxisX + halfExtentsOnAxisY; // top-right
		out[1] = _center - halfExtentsOnAxisX + halfExtentsOnAxisY; // top-left
		out[2] = _center - halfExtentsOnAxisX - halfExtentsOnAxisY; // bottom-left
		out[3] = _center + halfExtentsOnAxisX - halfExtentsOnAxisY; // bottom-right
	}

	float Obb2d::ProjectExtent(const glm::vec2 &axis) const
	{
		// Sum of absolute projections of half-extents onto axis
		return std::abs(glm::dot(axis, _axisX)) * _halfExtents.x +
			   std::abs(glm::dot(axis, _axisY)) * _halfExtents.y;
	}
}
