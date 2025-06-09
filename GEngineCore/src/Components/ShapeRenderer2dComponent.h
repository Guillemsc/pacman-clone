//
// Created by guillem on 6/8/25.
//

#ifndef SHAPERENDERER2DCOMPONENT_H
#define SHAPERENDERER2DCOMPONENT_H

#include "Component.h"
#include "ComponentType.h"

namespace GEngineCore
{
	class ShapeRenderer2dComponent : public Component
	{
	public:
		explicit ShapeRenderer2dComponent(const std::weak_ptr<Entity> &entity);

		static ComponentType GetTypeStatic() { return ComponentType::SHAPE_RENDERER_2D; }
		ComponentType GetType() override { return GetTypeStatic(); }
		const char* GetTypeName() override { return "ShapeRenderer2d"; }

		void OnTick() override;
		void OnDestroy() override;
	};
}

#endif //SHAPERENDERER2DCOMPONENT_H
