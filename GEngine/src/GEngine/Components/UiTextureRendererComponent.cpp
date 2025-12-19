//
// Created by guillem on 12/19/25.
//

#include "UiTextureRendererComponent.h"

#include "UiTransformComponent.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Data/UiRect.h"
#include "GEngine/Extensions/MathExtensions.h"
#include "GEngine/Modules/RenderingModule.h"
#include "GEngine/Resources/TextureResource.h"

namespace GEngine
{
	UiTextureRendererComponent::UiTextureRendererComponent(GEngineCoreModules *modules, const std::weak_ptr<Entity> &entity)
		: Component(modules, entity)
	{
		_preserveAspectRatio = _properties.Register<bool>("Perserve Aspect Ratio", false);
		_color = _properties.Register<Color01>("Color", Color01::White);
	}

	void UiTextureRendererComponent::OnTick()
	{
		const std::shared_ptr<TextureResource> texture = _textureResource.lock();
		if (!texture) return;

		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return;

		const std::shared_ptr<UiTransformComponent> transform = entity->GetUiTransform().lock();
		if (!transform) return;

		const UiRect uiRect = transform->GetWorldUiRect();

		const Texture rawTexture = texture->GetRawTexture();
		const glm::vec2 position = uiRect.GetPositionWithAppliedPivot();
		glm::vec2 size = uiRect.size;
		const float rotation = uiRect.rotation;
		const glm::vec2 pivot = uiRect.pivot;

		if (size.x <= 0.0f || size.y <= 0.0f) return;

		const bool preserveAspectRatio = _preserveAspectRatio->GetValue();

		if (preserveAspectRatio)
		{
			const float textureAspectRatio = MathExtensions::SafeDivide(rawTexture.width, rawTexture.height);
			const float sizeAspectRatio = MathExtensions::SafeDivide(size.x, size.y);

			if (sizeAspectRatio > textureAspectRatio)
			{
				size.x = size.y * textureAspectRatio;
			}
			else
			{
				size.y = MathExtensions::SafeDivide(size.x, textureAspectRatio);
			}
		}

		modules->rendering->UiRender()->AddTexture(
			entity->GetRenderingPositionInHierarchy(),
			rawTexture,
			position,
			rotation,
			size,
			pivot,
			_color->GetValue()
			);
	}

	void UiTextureRendererComponent::SetPreserveAspectRatio(const bool preserveAspectRatio) const
	{
		_preserveAspectRatio->SetValue(preserveAspectRatio);
	}

	void UiTextureRendererComponent::SetTexture(const std::weak_ptr<TextureResource> &texture)
	{
		_textureResource = texture;
	}
}
