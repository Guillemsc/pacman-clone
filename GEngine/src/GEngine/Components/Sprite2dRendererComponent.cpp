//
// Created by guillem on 12/1/25.
//

#include "Sprite2dRendererComponent.h"

#include "TransformComponent.h"
#include "GEngine/Extensions/RayLibExtensions.h"
#include "GEngine/Modules/RenderingModule.h"
#include "GEngine/Rendering/Renderer2d.h"
#include "GEngine/Resources/SpriteResource.h"
#include "GEngine/Resources/TextureResource.h"
#include "glm/vec2.hpp"

namespace GEngine
{
	Sprite2dRendererComponent::Sprite2dRendererComponent(
		GEngineCoreModules *modules,
		const std::weak_ptr<Entity> &entity
		)
		: Component(modules, entity)
	{
		_layer = _properties.Register("Layer", 0);
		_spriteResource = _properties.Register("Sprite", std::weak_ptr<SpriteResource>());
		_spriteIndex = _properties.Register("Sprite Index", 0);
	}

	void Sprite2dRendererComponent::OnTick()
	{
		const std::shared_ptr<SpriteResource> sprite = _spriteResource->GetValue().lock();
		if (!sprite) return;

		const int rectanglesCount = sprite->GetRectanglesCount();
		if (rectanglesCount == 0) return;

		const int rectangleIndex = _spriteIndex->GetValue();

		const std::shared_ptr<TextureResource> texture = sprite->GetTextureResource().lock();
		if (!texture) return;

		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return;

		const std::shared_ptr<TransformComponent> transform = entity->GetTransform().lock();
		if (!transform) return;

		const Texture2D& rawTexture = texture->GetRawTexture();

		glm::vec2 position = transform->GetPositionXY();
		position.y = -position.y;

		float rotation = transform->GetRotationEulerDegreesZ();
		glm::vec2 scale = transform->GetScaleXY();

		Rectangle rectangle = sprite->GetRectangle(rectangleIndex);

		position.x -= rectangle.width * 0.5f * scale.x;
		position.y -= rectangle.height * 0.5f * scale.y;

		modules->rendering->Render2d()->Add(_layer->GetValue(), [position, rotation, scale, rawTexture, rectangle]()
		{
			RayLibExtensions::DrawTextureEx(
				rawTexture,
				rectangle,
				{ position.x, position.y },
				rotation,
				{ scale.x, scale.y },
				WHITE
				);
		});
	}

	void Sprite2dRendererComponent::SetLayer(const int layer) const
	{
		_layer->SetValue(layer);
	}

	void Sprite2dRendererComponent::SetSprite(const std::weak_ptr<SpriteResource>& sprite) const
	{
		_spriteResource->SetValue(sprite);
	}

	void Sprite2dRendererComponent::SetSpriteIndex(const int index) const
	{
		_spriteIndex->SetValue(index);
	}

	std::weak_ptr<SpriteResource> Sprite2dRendererComponent::GetSprite() const
	{
		return _spriteResource->GetValue();
	}

	int Sprite2dRendererComponent::GetSpriteIndex() const
	{
		return _spriteIndex->GetValue();
	}
}
