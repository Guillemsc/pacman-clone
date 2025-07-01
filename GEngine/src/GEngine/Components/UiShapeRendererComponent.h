//
// Created by guillem on 7/1/25.
//

#ifndef UISHAPERENDERERCOMPONENT_H
#define UISHAPERENDERERCOMPONENT_H
#include "Component.h"

namespace GEngine
{
	class UiShapeRendererComponent : public Component
	{
	public:
		explicit UiShapeRendererComponent(const std::weak_ptr<Entity> &entity);

		constexpr const char* GetTypeName() override { return "Ui Shape Renderer"; }

		void OnTick() override;
	};
}

#endif //UISHAPERENDERERCOMPONENT_H
