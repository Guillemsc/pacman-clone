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

		REGISTER_COMPONENT(UiTransformComponent)

	public:
		explicit UiTransformComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity);

		void OnDrawSelectedGuizmo() override;

		void SetAnchors(const glm::vec4& anchors) const;
		void SetAnchoredPosition(const glm::vec2& anchoredPosition) const;
		void SetSizeDelta(const glm::vec2& sizeDelta) const;
		void SetPivot(const glm::vec2& pivot) const;
		void SetRotation(const float rotation) const;
		bool IsContainedInWorldRect(const glm::vec2& screenPosition) const;

		void SetWorldPosition(const glm::vec2& worldPosition) const;

		glm::vec2 GetScreenPosition() const;
		glm::vec2 GetScreenSize() const;
		float GetRotation() const;
		glm::vec2 GetPivot() const;

		UiRect GetWorldUiRect() const;

		glm::vec2 GetAnchoredPosition() const;
		glm::vec2 GetSizeDelta() const;

	private:
		void ComposeLocalUiRect();
		void RecalculateWorldUiRect();
		void RecalculateChildrenHierarchyWorldUiRects() const;
		UiRect GetParentWorldUiRect() const;

		CornersRect GetAnchorsScreenPosition(const UiRect& parentRect) const;
		void RecalculateLocalPositionAndLocalSizeFromAnchoredPositionAndSizeDelta() const;

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
