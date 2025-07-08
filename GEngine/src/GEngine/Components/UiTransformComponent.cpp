//
// Created by guillem on 7/1/25.
//

#include "UiTransformComponent.h"

#include "GEngine/Extensions/Vec4Extensions.h"
#include "GEngine/Modules/WindowModule.h"
#include "spdlog/spdlog.h"

namespace GEngine
{
	UiTransformComponent::UiTransformComponent(const std::weak_ptr<Entity> &entity) : Component(entity)
	{
		_localPosition = _properties.Register("Position", Vec2Extensions::Zero);
		_localSize = _properties.Register("Size", glm::vec2(100, 100));
		_localRotation = _properties.Register("Rotation", 0.0f);
		_localScale = _properties.Register("Scale", Vec2Extensions::One);
		_pivot = _properties.Register("Pivot", glm::vec2(0.5f, 0.5f));
		_anchors = _properties.Register("Anchors", glm::vec4(0.5f, 0.5f, 0.5f, 0.5f));
		_anchoredPosition = _properties.Register("Anchored Position", Vec2Extensions::Zero);
		_sizeDelta = _properties.Register("Size Delta", glm::vec2(50, 50));

		_localPosition->RegisterOnChanged([this](const glm::vec2&) {RefreshWhenLocalValueChanged();});
		_localSize->RegisterOnChanged([this](const glm::vec2&) {RefreshWhenLocalValueChanged();});
		_localRotation->RegisterOnChanged([this](const float&) {RefreshWhenLocalValueChanged();});
		_localScale->RegisterOnChanged([this](const glm::vec2&) {RefreshWhenLocalValueChanged();});
		_pivot->RegisterOnChanged([this](const glm::vec2&) {RefreshWhenLocalValueChanged();});
		_anchors->RegisterOnChanged([this](const glm::vec2&) {RefreshWhenLocalValueChanged();});
		_anchoredPosition->RegisterOnChanged([this](const glm::vec2&) {RefreshWhenLocalValueChanged();});
		_sizeDelta->RegisterOnChanged([this](const glm::vec2&) {RefreshWhenLocalValueChanged();});

		RefreshWhenLocalValueChanged();
	}

	void UiTransformComponent::SetAnchors(const glm::vec4& anchors) const
	{
		_anchors->SetValue(anchors);
	}

	void UiTransformComponent::SetAnchoredPosition(const glm::vec2 &anchoredPosition) const
	{
		_anchoredPosition->SetValue(anchoredPosition);
	}

	void UiTransformComponent::SetSizeDelta(const glm::vec2 &sizeDelta) const
	{
		_sizeDelta->SetValue(sizeDelta);
	}

	void UiTransformComponent::SetPivot(const glm::vec2 &pivot) const
	{
		_pivot->SetValue(pivot);
	}

	void UiTransformComponent::SetRotation(const float rotation) const
	{
		_localRotation->SetValue(rotation);
	}

	bool UiTransformComponent::IsContainedInScreenRect(const glm::vec2 &screenPosition) const
	{
		return false;
	}

	void UiTransformComponent::SetWorldPosition(const glm::vec2 &worldPosition) const
	{
		const UiRect parentRect = GetParentWorldUiRect();
		const glm::vec2 localPosition = worldPosition - parentRect.position;
		_localPosition->SetValue(localPosition);
	}

	glm::vec2 UiTransformComponent::GetScreenPosition() const
	{
		return _localPosition->GetValue();
	}

	glm::vec2 UiTransformComponent::GetScreenSize() const
	{
		return _localSize->GetValue();
	}

	float UiTransformComponent::GetRotation() const
	{
		return _localRotation->GetValue();
	}

	glm::vec2 UiTransformComponent::GetPivot() const
	{
		return _pivot->GetValue();
	}

	UiRect UiTransformComponent::GetWorldUiRect() const
	{
		return _worldUiRect;
	}

	glm::vec2 UiTransformComponent::GetAnchoredPosition() const
	{
		return _anchoredPosition->GetValue();
	}

	glm::vec2 UiTransformComponent::GetSizeDelta() const
	{
		return _sizeDelta->GetValue();
	}

	glm::vec4 UiTransformComponent::GetScreenRect() const
	{
		return {};
	}

	glm::vec2 UiTransformComponent::GetPivotScreenPosition() const
	{
		return  {};
	}

	glm::vec2 UiTransformComponent::GetPivotOffset() const
	{
		return  {};
	}

	void UiTransformComponent::ComposeLocalUiRect()
	{
		_localUiRect = {
			_localPosition->GetValue(),
			_localSize->GetValue(),
			_localRotation->GetValue(),
			_localScale->GetValue(),
			_pivot->GetValue()
		};
	}

	void UiTransformComponent::RecalculateWorldUiRect()
	{
		const UiRect parentUiRect = GetParentWorldUiRect();

		_worldUiRect = UiRect::Transform(parentUiRect, _localUiRect);
	}

	void UiTransformComponent::RecalculateChildrenHierarchyWorldUiRects() const
	{
		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return;

		entity->ForEachEntityInChildHierarchy(
			true,
			[this](const std::shared_ptr<Entity> &checkingEntity)
			{
				const std::shared_ptr<UiTransformComponent> childTransform = checkingEntity->GetUiTransform().lock();
				if (!childTransform) return false;

				childTransform->RecalculatePositionAndSizeFromAnchoredPositionAndSizeDelta();
				childTransform->ComposeLocalUiRect();
				childTransform->RecalculateWorldUiRect();
				return true;
			}
		);
	}

	glm::vec4 UiTransformComponent::GetAnchorsScreenPosition() const
	{
		const UiRect parentUiRect = GetParentWorldUiRect();
		const glm::vec4 anchors = _anchors->GetValue();

		return parentUiRect.GetRectFromNormalizedRect(anchors);
	}

	void UiTransformComponent::RecalculatePositionAndSizeFromAnchoredPositionAndSizeDelta() const
	{
		const glm::vec4 anchorsScreenRect = GetAnchorsScreenPosition();
		const glm::vec2 anchorsCenter = Vec4Extensions::GetCenter(anchorsScreenRect);
		const glm::vec2 anchorsSize = Vec4Extensions::GetSize(anchorsScreenRect);

		const glm::vec2 anchoredPosition = _anchoredPosition->GetValue();
		const glm::vec2 sizeDelta = _sizeDelta->GetValue();

		const glm::vec2 finalPosition = anchorsCenter + anchoredPosition;
		const glm::vec2 finalSize = anchorsSize + sizeDelta;

		const UiRect parentRect = GetParentWorldUiRect();
		const glm::vec2 localPosition = finalPosition - parentRect.position;
		_localPosition->SetValue(localPosition, false);

		_localSize->SetValue(finalSize, false);
	}

	void UiTransformComponent::RefreshWhenLocalValueChanged()
	{
		RecalculateChildrenHierarchyWorldUiRects();
	}

	void UiTransformComponent::Refresh()
	{
		RecalculateChildrenHierarchyWorldUiRects();
	}

	void UiTransformComponent::RecalculateScreenPositionAndSizeFromParentAndAnchoredPositionAndSizeDelta()
	{
		const UiRect parentScreenRect = GetParentWorldUiRect();
		//const glm::vec4 anchorsScreenPosition = GetAnchorsScreenRectFromParentScreenRect(parentScreenRect);

		// _screenRect.x = anchorsScreenPosition.x + _anchoredPosition.x - (_sizeDelta.x * 0.5f);
		// _screenRect.y = anchorsScreenPosition.y + _anchoredPosition.y - (_sizeDelta.y * 0.5f);
		// _screenRect.z = anchorsScreenPosition.z + _anchoredPosition.x + (_sizeDelta.x * 0.5f);
		// _screenRect.w = anchorsScreenPosition.w + _anchoredPosition.y + (_sizeDelta.y * 0.5f);
		//
		// const glm::vec2 pivotOffset = GetPivotOffset();
		//
		// _screenRect.x -= pivotOffset.x;
		// _screenRect.y -= pivotOffset.y;
		// _screenRect.z -= pivotOffset.x;
		// _screenRect.w -= pivotOffset.y;

		//const glm::vec2 pivotScreen = GetPivotScreenPosition();
		//_screenRect = Vec4Extensions::RotateAroundPivot(_screenRect, pivotScreen, _rotation->GetValue());
	}

	UiRect UiTransformComponent::GetParentWorldUiRect() const
	{
		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return {};

		const std::shared_ptr<Entity> parentEntity = entity->GetParent().lock();

		if (parentEntity)
		{
			const std::shared_ptr<UiTransformComponent> parentTransform = parentEntity->GetUiTransform().lock();

			if (parentTransform)
			{
				return parentTransform->_worldUiRect;
			}
		}

		const std::shared_ptr<GEngineCoreApplication> app = entity->GetApp().lock();
		if (!app) return {};

		const std::shared_ptr<WindowModule> window = app->Window().lock();
		if (!window) return {};

		const glm::vec2 screenSize = window->GetWindowSize();
		const glm::vec2 screenPosition = screenSize * 0.5f;

		return { screenPosition, screenSize, 0, Vec2Extensions::One };
	}

	glm::vec4 UiTransformComponent::GetAnchorsScreenRectFromParentScreenRect(const glm::vec4 &parentRect) const
	{
		glm::vec4 screenRect = glm::vec4(0);

		const glm::vec2 parentRectSize = Vec4Extensions::GetSize(parentRect);

		const glm::vec4 anchors = _anchors->GetValue();

		screenRect.x = parentRect.x + (parentRectSize.x * anchors.x);
		screenRect.y = parentRect.y + (parentRectSize.y * anchors.y);
		screenRect.z = parentRect.x + (parentRectSize.x * anchors.z);
		screenRect.w = parentRect.y + (parentRectSize.y * anchors.w);

		return screenRect;
	}

	void UiTransformComponent::RefreshChildrenHierarchy() const
	{
		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return;

		entity->ForEachEntityInChildHierarchy(
			true,
			[this](const std::shared_ptr<Entity> &checkingEntity)
			{
				const std::shared_ptr<UiTransformComponent> childTransform = checkingEntity->GetUiTransform().lock();
				if (!childTransform) return false;

				childTransform->RecalculateWorldUiRect();
				return true;
			}
		);
	}
} // GEngine