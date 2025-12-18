//
// Created by guillem on 12/1/25.
//

#include "Sprite2dRendererComponent.h"

#include "TransformComponent.h"
#include "GEngine/Core/GEngineCoreModules.h"
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
		_isFlippedX = _properties.Register("Flipped X", false);
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
		const glm::vec2 position = transform->GetPositionXY();
		const float rotation = transform->GetRotationEulerZ();
		const glm::vec2 scale = transform->GetScaleXY();

		rlRectangle rectangle = sprite->GetRectangle(rectangleIndex);

		if (_isFlippedX->GetValue())
		{
			rectangle.width *= -1.0f;
		}

		modules->rendering->Render2d()->AddTexture(
			_layer->GetValue(),
			rawTexture,
			rectangle,
			position,
			rotation,
			scale,
			Color01::White
		);
	}

	void Sprite2dRendererComponent::SetLayer(const std::int32_t layer) const
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

	void Sprite2dRendererComponent::SetFlippedX(const bool flippedX) const
	{
		_isFlippedX->SetValue(flippedX);
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
