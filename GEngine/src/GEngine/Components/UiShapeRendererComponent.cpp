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

		const UiRect uiRect = transform->GetWorldUiRect();

		const glm::vec2 position = uiRect.GetPositionWithAppliedPivot();
		const glm::vec2 size = uiRect.size;
		const float rotation = uiRect.rotation;
		const glm::vec2 pivot = uiRect.pivot;

		if (const auto rectShape = std::dynamic_pointer_cast<RectUiShape2d>(_shape2d->GetValue()))
		{
			modules->rendering->UiRender()->AddRect(
				0,
				position,
				rotation,
				size,
				pivot,
				_color->GetValue()
				);
		}
	}

	void UiShapeRendererComponent::SetColor(const Color01& color) const
	{
		_color->SetValue(color);
	}
} // GEngine