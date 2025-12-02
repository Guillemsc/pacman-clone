//
// Created by guillem on 7/1/25.
//

#ifndef UISHAPERENDERERCOMPONENT_H
#define UISHAPERENDERERCOMPONENT_H

#include "Component.h"
#include "GEngine/Raylib/RaylibWrapper.h"
#include "GEngine/Colors/Color01.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	class RectUiShape2d;
	class UiShape2d;

	class UiShapeRendererComponent final : public Component, public std::enable_shared_from_this<UiShapeRendererComponent>
	{
		DECLARE_COMPONENT(UiShapeRendererComponent)

	public:
		explicit UiShapeRendererComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity);

		void OnTick() override;

		void SetColor(const Color01& color) const;

	private:
		void RenderRectUiShape2d(
			const glm::vec2& position,
			float rotation,
			const glm::vec2& size,
			const glm::vec2& center,
			const RectUiShape2d* rectShape
		) const;

	private:
		std::shared_ptr<Property<std::shared_ptr<UiShape2d>>> _shape2d;
		std::shared_ptr<Property<Color01>> _color;
	};
}

#endif //UISHAPERENDERERCOMPONENT_H
