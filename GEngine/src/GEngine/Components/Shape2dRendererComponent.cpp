//
// Created by guillem on 6/8/25.
//

#include "Shape2dRendererComponent.h"

#include "GEngine/Raylib/RaylibWrapper.h"
#include "TransformComponent.h"
#include "GEngine/Colors/Color01.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Extensions/Color01Extensions.h"
#include "GEngine/Modules/RenderingModule.h"
#include "GEngine/Rendering/Renderer2d.h"
#include "GEngine/Shapes2d/RectShape2d.h"

namespace GEngine
{
	Shape2dRendererComponent::Shape2dRendererComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity)
	: Component(modules, entity)
	{
		_layer = _properties.Register("Layer", 0);
		_shape2d = _properties.RegisterObject<Shape2d>("Shape", std::make_shared<RectShape2d>());
		_color = _properties.Register<Color01>("Color", Color01::White);
	}

	void Shape2dRendererComponent::OnTick()
	{
		if (!_shape2d) return;

		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (entity == nullptr) return;

		const std::shared_ptr<TransformComponent> transform = entity->GetTransform().lock();
		if (transform == nullptr) return;

		const glm::vec2 position = transform->GetPositionXY();
		const float rotation = transform->GetRotationEulerZ();
		const glm::vec2 scale = transform->GetScaleXY();

		if (const auto rectShape = std::dynamic_pointer_cast<RectShape2d>(_shape2d->GetValue()))
		{
			modules->rendering->Render2d()->AddRect(
				_layer->GetValue(),
				position,
				rotation,
				scale,
				rectShape->GetSize(),
				_color->GetValue()
				);
		}
	}

	void Shape2dRendererComponent::OnDestroy()
	{

	}

	void Shape2dRendererComponent::SetLayer(const std::int32_t layer) const
	{
		_layer->SetValue(layer);
	}

	void Shape2dRendererComponent::SetColor(const Color01 &color) const
	{
		_color->SetValue(color);
	}
} // GEngineCore