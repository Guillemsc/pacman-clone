//
// Created by guillem on 6/8/25.
//

#ifndef SHAPERENDERER2DCOMPONENT_H
#define SHAPERENDERER2DCOMPONENT_H

#include "Component.h"
#include "GEngine/Raylib/RaylibWrapper.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	struct Color01;
	class Shape2d;
	class RectShape2d;

	class Shape2dRendererComponent final : public Component
	{
		REGISTER_COMPONENT(Shape2dRendererComponent)

	public:
		explicit Shape2dRendererComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity);

		void OnTick() override;
		void OnDestroy() override;

		void SetRenderLayer(std::int32_t layer) const;
		void SetColor(const Color01& color) const;

	private:
		std::shared_ptr<Property<std::int32_t>> _renderLayer;
		std::shared_ptr<Property<std::shared_ptr<Shape2d>>> _shape2d;
		std::shared_ptr<Property<Color01>> _color;
	};
}

#endif //SHAPERENDERER2DCOMPONENT_H
