//
// Created by guillem on 6/9/25.
//

#include "Texture2dRendererComponent.h"

#include "TransformComponent.h"
#include "Extensions/RayLibExtensions.h"
#include "Modules/RenderingModule.h"
#include "Resources/TextureResource.h"

namespace GEngineCore
{
	Texture2dRendererComponent::Texture2dRendererComponent(const std::weak_ptr<Entity> &entity) : Component(entity)
	{
	}

	void Texture2dRendererComponent::OnTick()
	{
		const std::shared_ptr<TextureResource> texture = _texturePtr.lock();
		if (!texture) return;

		const std::shared_ptr<GEngineCoreApplication> app = GetApp().lock();
		if (app == nullptr) return;

		const std::shared_ptr<RenderingModule> rendering = app->Rendering().lock();
		if (rendering == nullptr) return;

		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (entity == nullptr) return;

		const std::shared_ptr<TransformComponent> transform = entity->GetTransform().lock();
		if (transform == nullptr) return;

		const Texture2D& rawTexture = texture->GetRawTexture();

		glm::vec2 position = transform->GetPositionXY();
		float rotation = transform->GetRotationEulerDegreesZ();
		glm::vec2 scale = transform->GetScaleXY();

		position.x -= rawTexture.width * 0.5f * scale.x;
		position.y -= rawTexture.height * 0.5f * scale.y;

		rendering->Render2D().lock()->Add(0, [position, rotation, scale, rawTexture]()
		{
			RayLibExtensions::DrawTextureEx(rawTexture, {position.x, position.y}, rotation, {scale.x, scale.y}, WHITE);
		});
	}

	void Texture2dRendererComponent::SetTexture(const std::weak_ptr<TextureResource> &texture)
	{
		_texturePtr = texture;
	}
} // GEngineCore