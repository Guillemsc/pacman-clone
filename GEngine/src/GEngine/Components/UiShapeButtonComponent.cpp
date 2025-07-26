//
// Created by guillem on 7/7/25.
//

#include "UiShapeButtonComponent.h"

#include "UiShapeRendererComponent.h"

namespace GEngine
{
	UiShapeButtonComponent::UiShapeButtonComponent(const std::weak_ptr<Entity> &entity): Component(entity)
	{
		SetState();
	}

	void UiShapeButtonComponent::OnMouseEnter()
	{
		SetState();
	}

	void UiShapeButtonComponent::OnMouseExit()
	{
		SetState();
	}

	void UiShapeButtonComponent::OnMouseDown()
	{
		SetState();
	}

	void UiShapeButtonComponent::OnMouseUp()
	{
		SetState();
	}

	void UiShapeButtonComponent::OnMouseClick()
	{
		SetState();

		_onClickEvent.Invoke();
	}

	SubscribeEvent<> & UiShapeButtonComponent::OnClick()
	{
		return _onClickEvent;
	}

	void UiShapeButtonComponent::SetState()
	{
		Color01 color = {1, 0, 0, 1};

		if (GetState() == UiRaycastTargetState::MOUSE_INSIDE)
		{
			color = {1, 1, 0, 1};
		}

		if (GetState() == UiRaycastTargetState::MOUSE_DOWN)
		{
			color = {0, 1, 0, 1};
		}

		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return;

		const std::shared_ptr<UiShapeRendererComponent> shape = entity->GetComponent<UiShapeRendererComponent>().lock();
		if (!shape) return;

		shape->SetColor(color);
	}
} // GEngine
