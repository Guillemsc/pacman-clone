//
// Created by guillem on 6/8/25.
//

#include "Shape2dRendererComponent.h"

#include "raylib.h"
#include "TransformComponent.h"
#include "GEngine/Modules/RenderingModule.h"
#include "GEngine/Shapes2d/RectShape2d.h"

namespace GEngine
{
	Shape2dRendererComponent::Shape2dRendererComponent(const std::weak_ptr<Entity> &entity) : Component(entity)
	{
		_layer = _properties.Register("Layer", 0);
		_shape2d = _properties.RegisterObject<Shape2d>("Shape", std::make_shared<RectShape2d>());
	}

	void Shape2dRendererComponent::OnTick()
	{
		const std::shared_ptr<GEngineCoreApplication> app = GetApp().lock();
		if (app == nullptr) return;

		const std::shared_ptr<RenderingModule> rendering = app->Rendering().lock();
		if (rendering == nullptr) return;

		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (entity == nullptr) return;

		const std::shared_ptr<TransformComponent> transform = entity->GetTransform().lock();
		if (transform == nullptr) return;

		if (!_shape2d) return;

		glm::vec2 position = transform->GetPositionXY();
		position.y = -position.y;
		float rotation = -transform->GetRotationEulerDegreesZ();
		glm::vec2 scale = transform->GetScaleXY();

		rendering->Render2D().lock()->Add(_layer->GetValue(), [position, rotation, scale, this]()
		{
			if (const auto rectShape = std::dynamic_pointer_cast<RectShape2d>(_shape2d->GetValue()))
			{
				RenderRectShape2d(position, rotation, scale, rectShape.get());
			}
		});
	}

	void Shape2dRendererComponent::OnDestroy()
	{

	}

	void Shape2dRendererComponent::SetLayer(const int layer) const
	{
		_layer->SetValue(layer);
	}

	void Shape2dRendererComponent::RenderRectShape2d(
		const glm::vec2& position,
		const float rotation,
		const glm::vec2& scale,
		const RectShape2d* rectShape
		) const
	{
		const glm::vec2 rectSize = rectShape->GetSize();

		const Vector2 size = {rectSize.x * scale.x, rectSize.y * scale.y};
		const Vector2 center = { size.x * 0.5f, size.y * 0.5f };

		const Rectangle rectangle = {
			position.x,
			position.y,
			size.x,
			size.y,
		};

		DrawRectanglePro(rectangle, center, rotation, _color);
	}
} // GEngineCore