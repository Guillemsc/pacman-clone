//
// Created by guillem on 12/2/25.
//

#ifndef COLLIDER2D_H
#define COLLIDER2D_H

#include <memory>
#include <vector>

#include "GEngine/Events/Event.h"
#include "GEngine/Obbs/Obb2d.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	struct Contact2dData;
	class Entity;
}

namespace GEngine
{
	class Collider2d
	{
		friend class Collisions2dModule;

	public:
		explicit Collider2d(const std::weak_ptr<Entity>& owner);

		void SetTRS(const glm::vec2& position, float rotationRadians, const glm::vec2& size);

		bool CanLayersCollide(const Collider2d* other) const;
		bool Intersects(const Collider2d* other) const;

		void SetLayer(std::uint32_t layer);
		void SetLayerMask(std::uint32_t mask);

		std::weak_ptr<Entity> GetOwner() const;

		RegistreEvent<const Contact2dData&>& OnContactStart();
		RegistreEvent<const Contact2dData&>& OnContactStay();
		RegistreEvent<const Contact2dData&>& OnContactEnd();

	private:
		std::weak_ptr<Entity> _owner;

		Obb2d _obb2d;
		std::uint32_t _layer = 0;
		std::uint32_t _layerMask = 0;

		Event<const Contact2dData&> _onContactStart;
		Event<const Contact2dData&> _onContactStay;
		Event<const Contact2dData&> _onContactEnd;
	};
}

#endif //COLLIDER2D_H
