//
// Created by guillem on 7/1/25.
//

#include "UiTransformComponent.h"

#include "GEngine/Extensions/Vec4Extensions.h"
#include "GEngine/Modules/WindowModule.h"
#include "GEngine/Rendering/GuizmoUiRenderer.h"
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

		_localPosition->RegisterOnChanged([this](const glm::vec2&) {RecalculateChildrenHierarchyWorldUiRects();});
		_localSize->RegisterOnChanged([this](const glm::vec2&) {RecalculateChildrenHierarchyWorldUiRects();});
		_localRotation->RegisterOnChanged([this](const float&) {RecalculateChildrenHierarchyWorldUiRects();});
		_localScale->RegisterOnChanged([this](const glm::vec2&) {RecalculateChildrenHierarchyWorldUiRects();});
		_pivot->RegisterOnChanged([this](const glm::vec2&) {RecalculateChildrenHierarchyWorldUiRects();});
		_anchors->RegisterOnChanged([this](const glm::vec2&) {RecalculateChildrenHierarchyWorldUiRects();});
		_anchoredPosition->RegisterOnChanged([this](const glm::vec2&) {RecalculateChildrenHierarchyWorldUiRects();});
		_sizeDelta->RegisterOnChanged([this](const glm::vec2&) {RecalculateChildrenHierarchyWorldUiRects();});

		RecalculateChildrenHierarchyWorldUiRects();
	}

	void UiTransformComponent::OnDrawSelectedGuizmo(GuizmoUiRenderer* guizmoUiRenderer)
	{
		const UiRect parentUiRect = GetParentWorldUiRect();
		const CornersRect anchorsScreenPosition = GetAnchorsScreenPosition(parentUiRect);
		guizmoUiRenderer->AddCircle(anchorsScreenPosition.topLeft, 5, Color01::Green);
		guizmoUiRenderer->AddCircle(anchorsScreenPosition.topRight, 5, Color01::Green);
		guizmoUiRenderer->AddCircle(anchorsScreenPosition.bottomLeft, 5, Color01::Green);
		guizmoUiRenderer->AddCircle(anchorsScreenPosition.bottomRight, 5, Color01::Green);

		const glm::vec2 pivotPosition = _worldUiRect.GetPivotPosition(_localUiRect.pivot);
		guizmoUiRenderer->AddCircle(pivotPosition, 5, Color01::Blue);

		const CornersRect cornersRect = _worldUiRect.GetCorners();
		guizmoUiRenderer->AddLineRect(cornersRect, 2, Color01::White);
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

	bool UiTransformComponent::IsContainedInWorldRect(const glm::vec2 &screenPosition) const
	{
		return _worldUiRect.ContainsPoint(screenPosition);
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

	void UiTransformComponent::ComposeLocalUiRect()
	{
		_localUiRect = {
			_localPosition->GetValue(),
			_localRotation->GetValue(),
			_localScale->GetValue(),
			_localSize->GetValue(),
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

				childTransform->RecalculateLocalPositionAndLocalSizeFromAnchoredPositionAndSizeDelta();
				childTransform->ComposeLocalUiRect();
				childTransform->RecalculateWorldUiRect();
				return true;
			}
		);
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

		return { screenPosition, 0, Vec2Extensions::One, screenSize, {0.5f, 0.5f } };
	}

	CornersRect UiTransformComponent::GetAnchorsScreenPosition(const UiRect& parentRect) const
	{
		const CornersRect cornersRect = parentRect.GetCorners();
		const glm::vec4 anchors = _anchors->GetValue();

		return cornersRect.GetFromNormalisedRect(anchors);
	}

	void UiTransformComponent::RecalculateLocalPositionAndLocalSizeFromAnchoredPositionAndSizeDelta() const
	{
		const UiRect parentUiRect = GetParentWorldUiRect();
		const CornersRect anchorsScreenRect = GetAnchorsScreenPosition(parentUiRect);
		const glm::vec2 anchorsCenter = anchorsScreenRect.GetCenter();
		const glm::vec2 anchorsSize = anchorsScreenRect.GetSize();

		glm::vec2 anchoredPosition = _anchoredPosition->GetValue();
		const glm::vec2 sizeDelta = _sizeDelta->GetValue();

		anchoredPosition *= parentUiRect.scale;
		anchoredPosition = MathExtensions::RotatePointAroundOrigin(anchoredPosition, -parentUiRect.rotation);

		const glm::vec2 finalPosition = anchorsCenter + anchoredPosition;
		const glm::vec2 finalSize = anchorsSize + sizeDelta;

		const UiRect parentRect = GetParentWorldUiRect();
		glm::vec2 localPosition = finalPosition - parentRect.position;

		localPosition = MathExtensions::RotatePointAroundOrigin(localPosition, parentUiRect.rotation);
		localPosition /= parentUiRect.scale;

		_localPosition->SetValue(localPosition, false);
		_localSize->SetValue(finalSize, false);
	}
} // GEngine