//
// Created by guillem on 6/9/25.
//

#include "Texture2dRendererComponent.h"

#include "TransformComponent.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Extensions/RayLibExtensions.h"
#include "GEngine/Modules/RenderingModule.h"
#include "GEngine/Rendering/Renderer2d.h"
#include "GEngine/Resources/TextureResource.h"

namespace GEngine
{
	Texture2dRendererComponent::Texture2dRendererComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity)
		: Component(modules, entity)
	{
	}

	void Texture2dRendererComponent::OnTick()
	{
		const std::shared_ptr<TextureResource> texture = _textureResource.lock();
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

		position.x -= rawTexture.width * 0.5f * scale.x;
		position.y -= rawTexture.height * 0.5f * scale.y;
	}

	void Texture2dRendererComponent::SetTexture(const std::weak_ptr<TextureResource> &texture)
	{
		_textureResource = texture;
	}
} // GEngineCore