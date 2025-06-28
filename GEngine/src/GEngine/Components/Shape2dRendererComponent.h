//
// Created by guillem on 6/8/25.
//

#ifndef SHAPERENDERER2DCOMPONENT_H
#define SHAPERENDERER2DCOMPONENT_H

#include "Component.h"

namespace GEngine
{
	class Shape2dRendererComponent final : public Component
	{
	public:
		explicit Shape2dRendererComponent(const std::weak_ptr<Entity> &entity);

		const char* GetTypeName() override { return "Shape2dRenderer"; }

		void OnTick() override;
		void OnDestroy() override;
	};
}

#endif //SHAPERENDERER2DCOMPONENT_H
