//
// Created by guillem on 12/3/25.
//

#ifndef COLLIDER2DCOMPONENT_H
#define COLLIDER2DCOMPONENT_H

#include "Component.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	struct Contact2dData;
	class Collider2d;

	class Collider2dComponent final : public Component
	{
		DECLARE_COMPONENT(Collider2dComponent)

	public:
		explicit Collider2dComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity);

		void OnEnable() override;
		void OnTick() override;
		void OnDisable() override;
		void OnDrawSelectedGuizmo() override;
		void OnDrawGuizmo() override;

		void SetLayer(std::uint32_t layer);
		void SetLayerMask(std::uint32_t mask);

		RegistreEvent<const Contact2dData&>& OnContactStart();
		RegistreEvent<const Contact2dData&>& OnContactStay();
		RegistreEvent<const Contact2dData&>& OnContactEnd();

	private:
		void WhenContactStart(const Contact2dData& contact) const;
		void WhenContactStay(const Contact2dData& contact) const;
		void WhenContactEnd(const Contact2dData& contact) const;

	private:
		std::shared_ptr<Property<glm::vec2>> _size;

		std::weak_ptr<Collider2d> _collider;
		std::uint32_t _layer = 0;
		std::uint32_t _layerMask = 0;

		Event<const Contact2dData&> _onContactStart;
		Event<const Contact2dData&> _onContactStay;
		Event<const Contact2dData&> _onContactEnd;
	};
}

#endif //COLLIDER2DCOMPONENT_H
