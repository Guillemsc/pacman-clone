//
// Created by guillem on 6/8/25.
//

#ifndef SHAPERENDERER2DCOMPONENT_H
#define SHAPERENDERER2DCOMPONENT_H

#include "Component.h"
#include "raylib.h"
#include "GEngine/Shapes2d/Shape2d.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	class RectShape2d;

	class Shape2dRendererComponent final : public Component
	{
	public:
		explicit Shape2dRendererComponent(const std::weak_ptr<Entity> &entity);

		constexpr const char* GetTypeName() override { return "Shape2dRenderer"; }

		void OnTick() override;
		void OnDestroy() override;

		void SetLayer(int layer) const;

	private:
		void RenderRectShape2d(
			const glm::vec2& position,
			float rotation,
			const glm::vec2& scale,
			const RectShape2d* rectShape
			) const;

	private:
		std::shared_ptr<Property<std::int32_t>> _layer;
		std::shared_ptr<Property<std::shared_ptr<Shape2d>>> _shape2d;
		Color _color = { 255, 255, 255, 255 };
	};
}

#endif //SHAPERENDERER2DCOMPONENT_H
