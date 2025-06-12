//
// Created by guillem on 6/8/25.
//

#ifndef SHAPERENDERER2DCOMPONENT_H
#define SHAPERENDERER2DCOMPONENT_H

#include "Component.h"
#include "ComponentType.h"

namespace GEngineCore
{
	class Shape2dRendererComponent : public Component
	{
	public:
		explicit Shape2dRendererComponent(const std::weak_ptr<Entity> &entity);

		static ComponentType GetTypeStatic() { return ComponentType::SHAPE_2D_RENDERER; }
		ComponentType GetType() override { return GetTypeStatic(); }
		const char* GetTypeName() override { return "Shape2dRenderer"; }

		void OnTick() override;
		void OnDestroy() override;
	};
}

#endif //SHAPERENDERER2DCOMPONENT_H
