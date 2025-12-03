//
// Created by guillem on 12/2/25.
//

#include "Collider2d.h"

#include <cmath>

#include "Contact2dData.h"

namespace GEngine
{
	Collider2d::Collider2d(const std::weak_ptr<Entity> &owner)
	{
		_owner = owner;
	}

	void Collider2d::SetTRS(const glm::vec2 &position, const float rotationRadians, const glm::vec2 &size)
	{
		_obb2d = Obb2d(position, size, rotationRadians);
	}

	bool Collider2d::CanLayersCollide(const Collider2d* other) const
	{
		return _layerMask & other->_layer;
	}

	bool Collider2d::Intersects(const Collider2d* other) const
	{
		const bool canCollide = CanLayersCollide(other);
		if(!canCollide) return false;

		return _obb2d.Intersects(other->_obb2d);
	}

	void Collider2d::SetLayer(const std::uint32_t layer)
	{
		_layer = layer;
	}

	void Collider2d::SetLayerMask(const std::uint32_t mask)
	{
		_layerMask = mask;
	}

	std::weak_ptr<Entity> Collider2d::GetOwner() const
	{
		return _owner;
	}

	RegistreEvent<const Contact2dData&>& Collider2d::OnContactStart()
	{
		return _onContactStart;
	}

	RegistreEvent<const Contact2dData&>& Collider2d::OnContactStay()
	{
		return _onContactStay;
	}

	RegistreEvent<const Contact2dData&>& Collider2d::OnContactEnd()
	{
		return _onContactEnd;
	}
}
