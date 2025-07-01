//
// Created by guillem on 7/1/25.
//

#include "UiTransformComponent.h"

#include "GEngine/Extensions/Vec4Extensions.h"
#include "GEngine/Modules/WindowModule.h"

namespace GEngine
{
	UiTransformComponent::UiTransformComponent(const std::weak_ptr<Entity> &entity) : TransformComponent(entity)
	{
		RecalculateScreenRectFromParentAndRectDelta();
	}

	void UiTransformComponent::SetAnchoredPosition(const glm::vec2 &anchoredPosition)
	{
		_anchoredPosition = anchoredPosition;

		RecalculateRectDeltaFromAnchoredPositionAndSizeDelta();
		RecalculateScreenRectFromParentAndRectDelta();
	}

	void UiTransformComponent::SetSizeDelta(const glm::vec2 &sizeDelta)
	{
		_sizeDelta = sizeDelta;

		RecalculateRectDeltaFromAnchoredPositionAndSizeDelta();
		RecalculateScreenRectFromParentAndRectDelta();
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
		RecalculateScreenRectFromParentAndRectDelta();
		RecalculateAnchoredPositionAndSizeDeltaFromScreenRect();
	}

	void UiTransformComponent::RecalculateScreenRectFromParentAndRectDelta()
	{
		const glm::vec4 parentScreenRect = GetParentScreenRect();
		const glm::vec4 anchorsScreenPosition = GetAnchorsScreenRectFromParentScreenRect(parentScreenRect);

		_screenRect.x = anchorsScreenPosition.x + _rectDelta.x;
		_screenRect.y = anchorsScreenPosition.y + _rectDelta.y;
		_screenRect.z = anchorsScreenPosition.z - _rectDelta.z;
		_screenRect.w = anchorsScreenPosition.w - _rectDelta.w;
	}

	void UiTransformComponent::RecalculateAnchoredPositionAndSizeDeltaFromScreenRect()
	{
		_sizeDelta = Vec4Extensions::GetSize(_screenRect);
		_anchoredPosition.x = _rectDelta.x + (_sizeDelta.x * 0.5f);
		_anchoredPosition.y = _rectDelta.y + (_sizeDelta.y * 0.5f);
	}

	void UiTransformComponent::RecalculateRectDeltaFromAnchoredPositionAndSizeDelta()
	{
		_rectDelta.x = _anchoredPosition.x - (_sizeDelta.x * 0.5f);
		_rectDelta.y = _anchoredPosition.y - (_sizeDelta.y * 0.5f);
		_rectDelta.z = _anchoredPosition.x + (_sizeDelta.x * 0.5f);
		_rectDelta.w = _anchoredPosition.y + (_sizeDelta.y * 0.5f);
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
} // GEngine