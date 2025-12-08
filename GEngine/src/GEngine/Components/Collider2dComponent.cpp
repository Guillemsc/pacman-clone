//
// Created by guillem on 12/3/25.
//

#include "Collider2dComponent.h"

#include "TransformComponent.h"
#include "GEngine/Colliders2d/Collider2d.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Extensions/Color01Extensions.h"
#include "GEngine/Modules/Collisions2dModule.h"
#include "GEngine/Modules/RenderingModule.h"

namespace GEngine
{
	Collider2dComponent::Collider2dComponent(GEngineCoreModules *modules, const std::weak_ptr<Entity> &entity)
		: Component(modules, entity)
	{
		_size = _properties.Register("Size", glm::vec2(10, 10));
	}

	void Collider2dComponent::OnEnable()
	{
		_collider = modules->collisions2d->AddCollider(GetEntity());

		const std::shared_ptr<Collider2d> collider = _collider.lock();

		collider->SetLayer(_layer);
		collider->SetLayerMask(_layerMask);
		collider->OnContactStart().Add(std::bind(&Collider2dComponent::WhenContactStart, this, std::placeholders::_1));
		collider->OnContactStay().Add(std::bind(&Collider2dComponent::WhenContactStay, this, std::placeholders::_1));
		collider->OnContactEnd().Add(std::bind(&Collider2dComponent::WhenContactEnd, this, std::placeholders::_1));
	}

	void Collider2dComponent::OnTick()
	{
		const std::shared_ptr<Collider2d> collider = _collider.lock();
		const std::shared_ptr<TransformComponent> transform = GetEntity().lock()->GetTransform().lock();

		const glm::vec2 position = transform->GetPositionXY();
		const float rotationRadians = transform->GetRotationEulerZ();
		const glm::vec2 size = transform->GetScaleXY() * _size->GetValue();

		collider->SetTRS(position, rotationRadians, size);
	}

	void Collider2dComponent::OnDisable()
	{
		modules->collisions2d->RemoveCollider(_collider);
	}

	void Collider2dComponent::OnDrawSelectedGuizmo()
	{
		const std::shared_ptr<TransformComponent> transform = GetEntity().lock()->GetTransform().lock();
		const glm::vec2 position = transform->GetPositionXY();
		const float rotationRadians = transform->GetRotationEulerZ();
		const glm::vec2 size = transform->GetScaleXY() * _size->GetValue();

		modules->rendering->Guizmo2dRender()->AddRect(position, size, rotationRadians, Color01(0, 1, 0, 0.5f));
	}

	void Collider2dComponent::OnDrawGuizmo()
	{
		OnDrawSelectedGuizmo();
	}

	void Collider2dComponent::SetLayer(const std::uint32_t layer)
	{
		_layer = layer;

		const std::shared_ptr<Collider2d> collider = _collider.lock();
		if (!collider) return;

		collider->SetLayer(layer);
	}

	void Collider2dComponent::SetLayerMask(const std::uint32_t mask)
	{
		_layerMask = mask;

		const std::shared_ptr<Collider2d> collider = _collider.lock();
		if (!collider) return;

		collider->SetLayerMask(mask);
	}

	void Collider2dComponent::SetSize(const glm::vec2 &size) const
	{
		_size->SetValue(size);
	}

	RegisterEvent<const Contact2dData&>& Collider2dComponent::OnContactStart()
	{
		return _onContactStart;
	}

	RegisterEvent<const Contact2dData&>& Collider2dComponent::OnContactStay()
	{
		return _onContactStay;
	}

	RegisterEvent<const Contact2dData&>& Collider2dComponent::OnContactEnd()
	{
		return _onContactEnd;
	}

	void Collider2dComponent::WhenContactStart(const Contact2dData& contact) const
	{
		_onContactStart.Invoke(contact);
	}

	void Collider2dComponent::WhenContactStay(const Contact2dData& contact) const
	{
		_onContactStay.Invoke(contact);
	}

	void Collider2dComponent::WhenContactEnd(const Contact2dData& contact) const
	{
		_onContactEnd.Invoke(contact);
	}
}
