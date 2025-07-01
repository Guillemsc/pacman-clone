//
// Created by guillem on 7/1/25.
//

#ifndef UITRANSFORMCOMPONENT_H
#define UITRANSFORMCOMPONENT_H

#include "TransformComponent.h"

namespace GEngine
{
	class UiTransformComponent final : public TransformComponent
	{
		friend class EntitiesModule;

	public:
		explicit UiTransformComponent(const std::weak_ptr<Entity> &entity);

		constexpr const char* GetTypeName() override { return "Ui Transform"; }

		void SetAnchoredPosition(const glm::vec2& anchoredPosition);
		void SetSizeDelta(const glm::vec2& sizeDelta);

		glm::vec2 GetAnchoredPosition() const;
		glm::vec2 GetSizeDelta() const;

		glm::vec4 GetScreenRect() const;

	private:
		void Refresh();
		void RecalculateScreenRectFromParentAndRectDelta();
		void RecalculateAnchoredPositionAndSizeDeltaFromScreenRect();
		void RecalculateRectDeltaFromAnchoredPositionAndSizeDelta();
		glm::vec4 GetParentScreenRect() const;
		glm::vec4 GetAnchorsScreenRectFromParentScreenRect(const glm::vec4& parentRect) const;

	private:
		glm::vec4 _anchors = glm::vec4(0.5f, 0.5f, 0.5f, 0.5f);
		glm::vec4 _rectDelta = glm::vec4(-50, -50, -50, -50);
		glm::vec2 _anchoredPosition = glm::vec2(0);
		glm::vec2 _sizeDelta = glm::vec2(0);
		glm::vec4 _screenRect = glm::vec4(0, 0, 0, 0);
	};
}

#endif //UITRANSFORMCOMPONENT_H
