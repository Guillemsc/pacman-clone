//
// Created by guillem on 7/26/25.
//

#include "UiTextRendererComponent.h"

#include "UiTransformComponent.h"
#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Data/UiRect.h"
#include "GEngine/Modules/RenderingModule.h"
#include "GEngine/Rendering/UiRenderer.h"
#include "GEngine/Resources/FontResource.h"

namespace GEngine
{
	UiTextRendererComponent::UiTextRendererComponent(GEngineCoreModules* modules, const std::weak_ptr<Entity> &entity)
	: Component(modules, entity)
	{
	}

	void UiTextRendererComponent::OnTick()
	{
		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return;

		const std::shared_ptr<UiTransformComponent> transform = entity->GetUiTransform().lock();
		if (!transform) return;

		const UiRect uiRect = transform->GetWorldUiRect();
		glm::vec2 position = uiRect.position;

		position = modules->rendering->UiRender()->PositionToRenderPosition(position);

		const std::shared_ptr<FontResource> fontResource = _fontResource.lock();

		Font rawFont;

		if (fontResource)
		{
			rawFont = fontResource->_rawFont;
		}
		else
		{
			rawFont = GetFontDefault();
		}

		modules->rendering->UiRender()->Add(0, [this, position, rawFont]()
		{
			rlDrawTextEx(rawFont, _text.c_str(), Vector2(position.x, position.y), static_cast<float>(rawFont.baseSize), 2, MAROON);
		});
	}
}
