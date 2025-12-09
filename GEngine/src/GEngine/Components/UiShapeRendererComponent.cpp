//
// Created by guillem on 7/1/25.
//

#include "UiShapeRendererComponent.h"

#include "TransformComponent.h"
#include "UiTransformComponent.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Extensions/Color01Extensions.h"
#include "GEngine/Extensions/Vec4Extensions.h"
#include "GEngine/Modules/RenderingModule.h"
#include "GEngine/Rendering/UiRenderer.h"
#include "GEngine/Shapes2d/RectShape2d.h"
#include "GEngine/UiShapes2d/RectUiShape2d.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	UiShapeRendererComponent::UiShapeRendererComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity)
	: Component(modules, entity)
	{
		_shape2d = _properties.RegisterObject<UiShape2d>("Shape", std::make_shared<RectUiShape2d>());
		_color = _properties.Register<Color01>("Color", Color01::White);
	}

	void UiShapeRendererComponent::OnTick()
	{
		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (entity == nullptr) return;

		const std::shared_ptr<UiTransformComponent> transform = entity->GetUiTransform().lock();
		if (transform == nullptr) return;

		UiRect uiRect = transform->GetWorldUiRect();

		glm::vec2 position = uiRect.position;
		glm::vec2 size = uiRect.size;
		const float rotation = glm::degrees(uiRect.rotation);

		glm::vec2 pivot = uiRect.pivot;
		pivot.y = 1 - pivot.y;

		const glm::vec2 center = { size.x * pivot.x, size.y * pivot.y };

		const glm::vec2 offset = uiRect.GetPivotOffset();
		position += offset;

		position = modules->rendering->UiRender()->PositionToRenderPosition(position);

		auto selfPtr = weak_from_this();

		modules->rendering->UiRender()->Add(0, [selfPtr, size, rotation, center, position]()
		{
			const auto self = selfPtr.lock();
			if (!self) return;

			if (const auto rectShape = std::dynamic_pointer_cast<RectUiShape2d>(self->_shape2d->GetValue()))
			{
				self->RenderRectUiShape2d(position, rotation, size, center, rectShape.get());
			}
		});
	}

	void UiShapeRendererComponent::SetColor(const Color01& color) const
	{
		_color->SetValue(color);
	}

	void UiShapeRendererComponent::RenderRectUiShape2d(
		const glm::vec2 &position,
		const float rotation,
		const glm::vec2 &size,
		const glm::vec2 &center,
		const RectUiShape2d *rectShape
		) const
	{
		const Color color = Color01Extensions::ToRaylibColor(_color->GetValue());
		const rlRectangle button = {position.x, position.y, size.x, size.y};
		DrawRectanglePro(button, { center.x, center.y }, rotation, color);
		DrawText("Click Me", button.x + 10, button.y + 15, 20, BLACK);
	}
} // GEngine