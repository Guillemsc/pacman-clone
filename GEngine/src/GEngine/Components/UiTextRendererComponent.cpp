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

		const std::shared_ptr<FontResource> fontResource = _fontResource.lock();

		modules->rendering->UiRender()->AddText(
			entity->GetRenderingPositionInHierarchy(),
			fontResource.get(),
			std::string_view(_text),
			uiRect.position,
			uiRect.rotation,
			uiRect.size,
			uiRect.pivot,
			_wordSpacing,
			Color01::White,
			_horizontalAlign,
			_verticalAlign
			);
	}

	std::string UiTextRendererComponent::GetText() const
	{
		return _text;
	}

	void UiTextRendererComponent::SetText(const std::string &text)
	{
		_text = text;
	}

	HorizontalTextAlign UiTextRendererComponent::GetHorizontalAlign() const
	{
		return _horizontalAlign;
	}

	void UiTextRendererComponent::SetHorizontalAlign(const HorizontalTextAlign horizontalAlign)
	{
		_horizontalAlign = horizontalAlign;
	}

	VerticalTextAlign UiTextRendererComponent::GetVerticalAlign() const
	{
		return _verticalAlign;
	}

	void UiTextRendererComponent::SetVerticalAlign(const VerticalTextAlign verticalAlign)
	{
		_verticalAlign = verticalAlign;
	}

	float UiTextRendererComponent::GetWordSpacing() const
	{
		return _wordSpacing;
	}

	void UiTextRendererComponent::SetWordSpacing(const float wordSpacing)
	{
		_wordSpacing = wordSpacing;
	}
}
