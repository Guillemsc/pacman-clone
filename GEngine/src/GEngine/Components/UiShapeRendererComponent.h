//
// Created by guillem on 7/1/25.
//

#ifndef UISHAPERENDERERCOMPONENT_H
#define UISHAPERENDERERCOMPONENT_H
#include "Component.h"
#include "raylib.h"
#include "GEngine/Colors/Color01.h"

namespace GEngine
{
	class UiShapeRendererComponent final : public Component
	{
	public:
		explicit UiShapeRendererComponent(const std::weak_ptr<Entity> &entity);

		constexpr const char* GetTypeName() override { return "Ui Shape Renderer"; }

		void OnTick() override;

		void SetColor(const Color01& color);

	private:
		Color01 _color = Color01::White;
	};
}

#endif //UISHAPERENDERERCOMPONENT_H
