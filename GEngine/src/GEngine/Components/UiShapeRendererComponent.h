//
// Created by guillem on 7/1/25.
//

#ifndef UISHAPERENDERERCOMPONENT_H
#define UISHAPERENDERERCOMPONENT_H
#include "Component.h"
#include "raylib.h"

namespace GEngine
{
	class UiShapeRendererComponent final : public Component
	{
	public:
		explicit UiShapeRendererComponent(const std::weak_ptr<Entity> &entity);

		constexpr const char* GetTypeName() override { return "Ui Shape Renderer"; }

		void OnTick() override;

		void SetColor(const Color &color);

	private:
		Color _color = { 255, 255, 255, 255 };
	};
}

#endif //UISHAPERENDERERCOMPONENT_H
