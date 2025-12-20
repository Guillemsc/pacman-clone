//
// Created by guillem on 12/19/25.
//

#include "UiRenderersAlphaGroupComponent.h"

namespace GEngine
{
	UiRenderersAlphaGroupComponent::UiRenderersAlphaGroupComponent(GEngineCoreModules *modules, const std::weak_ptr<Entity> &entity)
		: Component(modules, entity)
	{
		_alpha = _properties.Register("Alpha", 1.0f);
	}

	void UiRenderersAlphaGroupComponent::SetAlpha(const float alpha) const
	{
		_alpha->SetValue(alpha);
	}

	float UiRenderersAlphaGroupComponent::GetAlpha() const
	{
		return _alpha->GetValue();
	}
}
