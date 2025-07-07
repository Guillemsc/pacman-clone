//
// Created by guillem on 7/1/25.
//

#ifndef UITRANSFORMCOMPONENT_H
#define UITRANSFORMCOMPONENT_H

#include "TransformComponent.h"

namespace GEngine
{
	class UiTransformComponent final : public Component
	{
		friend class EntitiesModule;

	public:
		explicit UiTransformComponent(const std::weak_ptr<Entity> &entity);

		constexpr const char* GetTypeName() override { return "Ui Transform"; }

		void SetAnchors(const glm::vec4& anchors);
		void SetAnchoredPosition(const glm::vec2& anchoredPosition);
		void SetSizeDelta(const glm::vec2& sizeDelta);
		void SetPivot(const glm::vec2& pivot);

		glm::vec2 GetAnchoredPosition() const;
		glm::vec2 GetSizeDelta() const;

		glm::vec4 GetScreenRect() const;

	private:
		void Refresh();
		void RecalculateScreenRectFromParentAndAnchoredPositionAndSizeDelta();
		glm::vec4 GetParentScreenRect() const;
		glm::vec4 GetAnchorsScreenRectFromParentScreenRect(const glm::vec4& parentRect) const;
		void RefreshChildrenHierarchy() const;

	private:
		glm::vec4 _anchors = glm::vec4(0.5f);
		glm::vec2 _anchoredPosition = glm::vec2(0);
		glm::vec2 _sizeDelta = glm::vec2(100);
		glm::vec2 _pivot = glm::vec2(0.5f);
		glm::vec4 _screenRect = glm::vec4(0);
	};
}

#endif //UITRANSFORMCOMPONENT_H
