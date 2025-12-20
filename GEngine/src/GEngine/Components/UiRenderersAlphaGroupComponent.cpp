//
// Created by guillem on 12/19/25.
//

#include "UiRenderersAlphaGroupComponent.h"

#include "GEngine/Entities/EntityParentHierarchyIterator.h"

namespace GEngine
{
	UiRenderersAlphaGroupComponent::UiRenderersAlphaGroupComponent(GEngineCoreModules *modules, const std::weak_ptr<Entity> &entity)
		: Component(modules, entity)
	{
		_alpha = _properties.Register("Alpha", 1.0f);
	}

	float UiRenderersAlphaGroupComponent::GetAlphaMultiplier(const std::weak_ptr<Entity> &entity)
	{
		float alpha = 1.0f;

		EntityParentHierarchyIterator iterator(entity);

		while (iterator.HasNext())
		{
			Entity* next = iterator.GetNext();

			const std::shared_ptr<UiRenderersAlphaGroupComponent> alphaGroup = next->GetComponent<UiRenderersAlphaGroupComponent>().lock();
			if (!alphaGroup) continue;

			alpha *= alphaGroup->GetAlpha();
		}

		return alpha;
	}

	void UiRenderersAlphaGroupComponent::SetAlpha(const float alpha) const
	{
		_alpha->SetValue(std::clamp(alpha, 0.0f, 1.0f));
	}

	float UiRenderersAlphaGroupComponent::GetAlpha() const
	{
		return _alpha->GetValue();
	}
}
