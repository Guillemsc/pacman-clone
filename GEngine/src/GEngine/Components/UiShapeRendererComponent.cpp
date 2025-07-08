//
// Created by guillem on 7/1/25.
//

#include "UiShapeRendererComponent.h"

#include "TransformComponent.h"
#include "UiTransformComponent.h"
#include "GEngine/Extensions/Color01Extensions.h"
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

		UiRect uiRect = transform->GetWorldUiRect();

		glm::vec2 position = uiRect.position;
		glm::vec2 size = uiRect.size;
		float rotation = glm::degrees(uiRect.rotation);

		glm::vec2 pivot = uiRect.pivot;
		pivot.y = 1 - pivot.y;

		const Vector2 center = { size.x * pivot.x, size.y * pivot.y };

		position = rendering->UiRender().lock()->PositionToRenderPosition(position);

		rendering->UiRender().lock()->Add(0, [this, size, rotation, center, position]()
		{
			const Color color = Color01Extensions::ToRaylibColor(_color);
			const Rectangle button = { position.x, position.y, size.x, size.y};
			DrawRectanglePro(button, center, rotation, color);
			DrawText("Click Me", button.x + 10, button.y + 15, 20, BLACK);
		});
	}

	void UiShapeRendererComponent::SetColor(const Color01& color)
	{
		_color = color;
	}
} // GEngine