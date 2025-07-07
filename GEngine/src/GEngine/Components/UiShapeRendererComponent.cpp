//
// Created by guillem on 7/1/25.
//

#include "UiShapeRendererComponent.h"

#include "TransformComponent.h"
#include "UiTransformComponent.h"
#include "GEngine/Extensions/Vec4Extensions.h"
#include "GEngine/Modules/RenderingModule.h"
#include "GEngine/Rendering/UiRenderer.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	UiShapeRendererComponent::UiShapeRendererComponent(const std::weak_ptr<Entity> &entity) : Component(entity)
	{

	}

	void UiShapeRendererComponent::OnTick()
	{
		const std::shared_ptr<GEngineCoreApplication> app = GetApp().lock();
		if (app == nullptr) return;

		const std::shared_ptr<RenderingModule> rendering = app->Rendering().lock();
		if (rendering == nullptr) return;

		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (entity == nullptr) return;

		const std::shared_ptr<UiTransformComponent> transform = entity->GetUiTransform().lock();
		if (transform == nullptr) return;

		glm::vec4 rect = transform->GetScreenRect();
		glm::vec2 size = Vec4Extensions::GetSize(rect);
		rect = rendering->UiRender().lock()->RectToRenderRect(rect);

		rendering->UiRender().lock()->Add(0, [this, rect, size]()
		{
			const Rectangle button = { rect.x, rect.y, size.x, size.y};
			DrawRectangleRec(button, _color);
			DrawText("Click Me", button.x + 10, button.y + 15, 20, BLACK);
		});
	}

	void UiShapeRendererComponent::SetColor(const Color &color)
	{
		_color = color;
	}
} // GEngine