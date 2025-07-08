//
// Created by guillem on 7/1/25.
//

#ifndef UITRANSFORMCOMPONENT_H
#define UITRANSFORMCOMPONENT_H

#include "TransformComponent.h"
#include "GEngine/Data/UiRect.h"

namespace GEngine
{
	class UiTransformComponent final : public Component
	{
		friend class EntitiesModule;

	public:
		explicit UiTransformComponent(const std::weak_ptr<Entity> &entity);

		constexpr const char* GetTypeName() override { return "Ui Transform"; }

		void SetAnchors(const glm::vec4& anchors) const;
		void SetAnchoredPosition(const glm::vec2& anchoredPosition) const;
		void SetSizeDelta(const glm::vec2& sizeDelta) const;
		void SetPivot(const glm::vec2& pivot) const;
		void SetRotation(const float rotation) const;
		bool IsContainedInScreenRect(const glm::vec2& screenPosition) const;

		void SetWorldPosition(const glm::vec2& worldPosition) const;

		glm::vec2 GetScreenPosition() const;
		glm::vec2 GetScreenSize() const;
		float GetRotation() const;
		glm::vec2 GetPivot() const;

		UiRect GetWorldUiRect() const;

		glm::vec2 GetAnchoredPosition() const;
		glm::vec2 GetSizeDelta() const;
		glm::vec4 GetScreenRect() const;
		glm::vec2 GetPivotScreenPosition() const;
		glm::vec2 GetPivotOffset() const;

	private:
		void ComposeLocalUiRect();
		void RecalculateWorldUiRect();
		void RecalculateChildrenHierarchyWorldUiRects() const;

		glm::vec4 GetAnchorsScreenPosition() const;
		void RecalculatePositionAndSizeFromAnchoredPositionAndSizeDelta() const;

		void RefreshWhenLocalValueChanged();

		void Refresh();
		void RecalculateScreenPositionAndSizeFromParentAndAnchoredPositionAndSizeDelta();
		UiRect GetParentWorldUiRect() const;
		glm::vec4 GetAnchorsScreenRectFromParentScreenRect(const glm::vec4& parentRect) const;
		void RefreshChildrenHierarchy() const;

	private:
		std::shared_ptr<Property<glm::vec2>> _localPosition;
		std::shared_ptr<Property<glm::vec2>> _localSize;
		std::shared_ptr<Property<float>> _localRotation;
		std::shared_ptr<Property<glm::vec2>> _localScale;
		std::shared_ptr<Property<glm::vec2>> _pivot;

		std::shared_ptr<Property<glm::vec4>> _anchors;
		std::shared_ptr<Property<glm::vec2>> _anchoredPosition;
		std::shared_ptr<Property<glm::vec2>> _sizeDelta;

		UiRect _localUiRect;
		UiRect _worldUiRect;
	};
}

#endif //UITRANSFORMCOMPONENT_H
