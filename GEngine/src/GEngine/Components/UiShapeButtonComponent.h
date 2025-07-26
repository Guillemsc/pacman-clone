//
// Created by guillem on 7/7/25.
//

#ifndef UIBUTTONCOMPONENT_H
#define UIBUTTONCOMPONENT_H

#include "Component.h"
#include "GEngine/UiRaycasting/UiRaycastTarget.h"

namespace GEngine
{
	class UiShapeButtonComponent final : public Component, public UiRaycastTarget
	{
	public:
		explicit UiShapeButtonComponent(const std::weak_ptr<Entity> &entity);

		constexpr const char* GetTypeName() override { return "Ui Shape Button"; }

		void OnMouseEnter() override;
		void OnMouseExit() override;
		void OnMouseDown() override;
		void OnMouseUp() override;
		void OnMouseClick() override;

		SubscribeEvent<>& OnClick();

	private:
		void SetState();

		Event<> _onClickEvent;
	};
}

#endif //UIBUTTONCOMPONENT_H
