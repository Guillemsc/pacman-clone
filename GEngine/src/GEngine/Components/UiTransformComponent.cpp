//
// Created by guillem on 7/1/25.
//

#include "UiTransformComponent.h"

#include "GEngine/Extensions/Vec4Extensions.h"
#include "GEngine/Modules/WindowModule.h"

namespace GEngine
{
	UiTransformComponent::UiTransformComponent(const std::weak_ptr<Entity> &entity) : Component(entity)
	{
		RecalculateScreenRectFromParentAndAnchoredPositionAndSizeDelta();
	}

	void UiTransformComponent::SetAnchors(const glm::vec4& anchors)
	{
		_anchors = anchors;

		RecalculateScreenRectFromParentAndAnchoredPositionAndSizeDelta();
		RefreshChildrenHierarchy();
	}

	void UiTransformComponent::SetAnchoredPosition(const glm::vec2 &anchoredPosition)
	{
		_anchoredPosition = anchoredPosition;

		RecalculateScreenRectFromParentAndAnchoredPositionAndSizeDelta();
		RefreshChildrenHierarchy();
	}

	void UiTransformComponent::SetSizeDelta(const glm::vec2 &sizeDelta)
	{
		_sizeDelta = sizeDelta;

		RecalculateScreenRectFromParentAndAnchoredPositionAndSizeDelta();
		RefreshChildrenHierarchy();
	}

	void UiTransformComponent::SetPivot(const glm::vec2 &pivot)
	{
		_pivot = pivot;

		RecalculateScreenRectFromParentAndAnchoredPositionAndSizeDelta();
		RefreshChildrenHierarchy();
	}

	glm::vec2 UiTransformComponent::GetAnchoredPosition() const
	{
		return _anchoredPosition;
	}

	glm::vec2 UiTransformComponent::GetSizeDelta() const
	{
		return _sizeDelta;
	}

	glm::vec4 UiTransformComponent::GetScreenRect() const
	{
		return _screenRect;
	}

	void UiTransformComponent::Refresh()
	{
		RecalculateScreenRectFromParentAndAnchoredPositionAndSizeDelta();
		RefreshChildrenHierarchy();
	}

	void UiTransformComponent::RecalculateScreenRectFromParentAndAnchoredPositionAndSizeDelta()
	{
		const glm::vec4 parentScreenRect = GetParentScreenRect();
		const glm::vec4 anchorsScreenPosition = GetAnchorsScreenRectFromParentScreenRect(parentScreenRect);

		glm::vec2 pivotOffset = {
			MathExtensions::Lerp(-_sizeDelta.x * 0.5f, _sizeDelta.x * 0.5f, _pivot.x),
			MathExtensions::Lerp(-_sizeDelta.y * 0.5f, _sizeDelta.y * 0.5f, _pivot.y)
			};

		_screenRect.x = anchorsScreenPosition.x + _anchoredPosition.x - pivotOffset.x - (_sizeDelta.x * 0.5f);
		_screenRect.y = anchorsScreenPosition.y + _anchoredPosition.y - pivotOffset.y - (_sizeDelta.y * 0.5f);
		_screenRect.z = anchorsScreenPosition.z + _anchoredPosition.x - pivotOffset.x + (_sizeDelta.x * 0.5f);
		_screenRect.w = anchorsScreenPosition.w + _anchoredPosition.y - pivotOffset.y + (_sizeDelta.y * 0.5f);
	}

	glm::vec4 UiTransformComponent::GetParentScreenRect() const
	{
		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return glm::vec4(0);

		const std::shared_ptr<Entity> parentEntity = entity->GetParent().lock();

		if (parentEntity)
		{
			const std::shared_ptr<UiTransformComponent> parentTransform = parentEntity->GetUiTransform().lock();

			if (parentTransform)
			{
				return parentTransform->_screenRect;
			}
		}

		const std::shared_ptr<GEngineCoreApplication> app = entity->GetApp().lock();
		if (!app) return glm::vec4(0);

		const std::shared_ptr<WindowModule> window = app->Window().lock();
		if (!window) return glm::vec4(0);

		const glm::vec2 screenSize = window->GetWindowSize();

		return { 0, 0, screenSize.x, screenSize.y };
	}

	glm::vec4 UiTransformComponent::GetAnchorsScreenRectFromParentScreenRect(const glm::vec4 &parentRect) const
	{
		glm::vec4 screenRect = glm::vec4(0);

		const glm::vec2 parentRectSize = Vec4Extensions::GetSize(parentRect);

		screenRect.x = parentRect.x + (parentRectSize.x * _anchors.x);
		screenRect.y = parentRect.y + (parentRectSize.y * _anchors.y);
		screenRect.z = parentRect.x + (parentRectSize.x * _anchors.z);
		screenRect.w = parentRect.y + (parentRectSize.y * _anchors.w);

		return screenRect;
	}

	void UiTransformComponent::RefreshChildrenHierarchy() const
	{
		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return;

		entity->ForEachEntityInChildHierarchy(
			false,
			[this](const std::shared_ptr<Entity> &checkingEntity)
			{
				const std::shared_ptr<UiTransformComponent> childTransform = checkingEntity->GetUiTransform().lock();
				if (!childTransform) return false;

				childTransform->Refresh();
				return true;
			}
		);
	}
} // GEngine