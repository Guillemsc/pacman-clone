//
// Created by guillem on 7/26/25.
//

#include "UiTextRendererComponent.h"

#include "UiTransformComponent.h"
#include "GEngine/Data/UiRect.h"
#include "GEngine/Modules/RenderingModule.h"
#include "GEngine/Rendering/UiRenderer.h"
#include "GEngine/Resources/FontResource.h"

namespace GEngine
{
	UiTextRendererComponent::UiTextRendererComponent(const std::weak_ptr<Entity> &entity): Component(entity)
	{
	}

	void UiTextRendererComponent::OnTick()
	{
		const std::shared_ptr<GEngineCoreApplication> app = GetApp().lock();
		if (!app) return;

		const std::shared_ptr<RenderingModule> rendering = app->Rendering().lock();
		if (!rendering) return;

		const std::shared_ptr<Entity> entity = GetEntity().lock();
		if (!entity) return;

		const std::shared_ptr<UiTransformComponent> transform = entity->GetUiTransform().lock();
		if (!transform) return;

		const UiRect uiRect = transform->GetWorldUiRect();
		glm::vec2 position = uiRect.position;

		position = rendering->UiRender().lock()->PositionToRenderPosition(position);

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

		rendering->UiRender().lock()->Add(0, [this, position, rawFont]()
		{
			DrawTextEx(rawFont, _text.c_str(), (Vector2){ position.x, position.y }, static_cast<float>(rawFont.baseSize), 2, MAROON);
		});
	}
}
